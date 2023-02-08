/**
 * @author Fatih Küçükkarakurt : https://github.com/fkkarakurt
 *  
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <set>
#include <map>
#include <time.h>

class Node
{
public:
    std::string stateName;
    std::vector<Node> outStates;

    void setStateName(std::string name)
    {
        stateName = name;
    }

    std::string getStateName()
    {
        return stateName;
    }
};

std::map<std::string, float> calculateFreq(std::vector<std::string> tokens)
{
    std::map<std::string, float> freq;
    std::map<std::string, float>::iterator mapItr;

    for (std::vector<std::string>::iterator itr = tokens.begin();
         itr != tokens.end();
         ++itr)
    {
        freq[*itr] = freq[*itr] + 1;
    }

    for (mapItr = freq.begin(); mapItr != freq.end(); ++mapItr)
    {
        std::cout << mapItr->first << " " << mapItr->second << std::endl;
    }

    return freq;
}

std::vector<Node> prepareGraph(std::vector<std::string> tokens)
{
    // Contains the unique states
    std::set<std::string> vocabStates;

    // Contains the unique states
    std::vector<Node> nodes;

    // stateName
    std::string stateName = "";

    unsigned idX, nidX, currentStateIdX, nextStateIdX;
    std::set<std::string>::iterator setItr;
    std::vector<Node>::iterator nodeItr;
    Node *node;
    Node currentNode, currentState, nextState;

    // Storing Tokens
    for (std::vector<std::string>::iterator itr = tokens.begin();
         itr != tokens.end();
         ++itr)
    {
        vocabStates.insert(*itr);
    }

    // Making set if stored tokens
    for (setItr = vocabStates.begin();
         setItr != vocabStates.end();
         setItr++)
    {
        node = new Node;
        node->setStateName(*setItr);
        nodes.push_back(*node);
    }

    // Creating Our Graph
    for (idX = 0; idX < tokens.size() - 1; idX++)
    {
        for (nidX = 0; nidX < nodes.size(); nidX++)
        {
            currentNode = nodes.at(nidX);
            if (currentNode.getStateName() == tokens.at(idX))
            {
                currentStateIdX = nidX;
            }
            if (currentNode.getStateName() == tokens.at(idX + 1))
            {
                nextStateIdX = nidX;
            }
        }
        nodes.at(currentStateIdX).outStates.push_back(nodes.at(nextStateIdX));
    }

    // Printing our values for verifying
    for (nidX = 0; nidX < nodes.size(); nidX++)
    {
        currentNode = nodes.at(nidX);
        for (idX = 0; idX < currentNode.outStates.size(); idX++)
        {
            stateName = currentNode.outStates.at(idX).getStateName();
            std::cout << currentNode.getStateName() << "==>";
            std::cout << "None" << std::endl;
        }
    }

    return nodes;
}

std::vector<Node> prepareData(std::string data)
{
    std::vector<Node> nodes;

    // Token is for storing all the words
    std::vector<std::string> tokens;

    std::map<std::string, float> probability;

    /**
     * Split the data by " " as delimiter and store it
     * in every word in token
     */
    std::istringstream iss(data);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(tokens));

    nodes = prepareGraph(tokens);
    std::cout << "----------------------" << std::endl;

    return nodes;
}

void generateText(std::vector<Node> markovGraph,
                  int nSampling,
                  std::string start,
                  bool stopAtEnd)
{
    bool outerBreak = false;
    std::string generatedText = "";
    generatedText += start;
    srand(time(NULL));

    for(int i = 0; i<nSampling;i++)
    {
        for(int j = 0; j<markovGraph.size();j++)
        {
            if(markovGraph.at(j).getStateName() == start)
            {
                if(markovGraph.at(j).outStates.size() == 0)
                {
                    generatedText = generatedText + " " + "end";
                    start = "end";
                    outerBreak = true;
                    break;
                }
                else if(markovGraph.at(j).outStates.size() == 1)
                {
                    generatedText = generatedText + " " + markovGraph.at(j).outStates.at(0).getStateName();
                    start = markovGraph.at(j).outStates.at(0).getStateName();
                    if(start == "end")
                    {
                        outerBreak = true;
                    }
                    break;
                }
                else
                {
                    int randomNumber = rand() % markovGraph.at(j).outStates.size();
                    generatedText = generatedText + " " + markovGraph.at(j).outStates.at(randomNumber).getStateName();
                    start = markovGraph.at(j).outStates.at(randomNumber).getStateName();
                    if(start == "end")
                    {
                        outerBreak = true;
                    }
                    break;
                }
            }
        }
        if(outerBreak && stopAtEnd)
        {
            break;
        }
    }
    std::cout << generatedText << std::endl;
}

int main()
{
    std::vector<Node> markovGraph;
    int nWords = 10;
    std::string startToken = "start";
    std::string trainData = "start My name is Fatih end start what is your name end start wonderful name Elif";
    trainData = "start the quick brown fox jumps over the brown fox who is slow jumps over the brown fox who is dead end";
    markovGraph = prepareData(trainData);
    generateText(markovGraph, nWords, startToken, true);
    generateText(markovGraph, nWords, startToken, false);
}