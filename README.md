# What is Markov Model?

Markof models, which are used in many science and engineering fields, including computer science, are actually an application of graph theory.

Simply, nodes are graphs that consist of states and have edges that model the statistical transition between these states.

According to Markof models (or Markov chain), a situation changes according to a certain statistical value or remains unchanged. In addition, past situations do not have an effect on the current situation. However, the current situation can affect future situations.

Due to the statistical nature of the Markov models, a representation that models the probability value of each [Stochastic Event](https://en.wikipedia.org/wiki/Stochastic_process) is possible.

## Compiling

### Clone

```sh
git clone https://github.com/fkkarakurt/markov-model-example.git Markov
cd Markov
```

Then, create a `build` folder and enter it.

```sh
mkdir build
cd build
```

### MinGW

```sh
cmake .. -G "MinGW Makefiles"
make
./Markov
```

### VS
```sh
cmake ..
```
If you are using Windows, the file with the `.sln` extension is created. Open it.

### g++
```sh
g++ markov.cpp -o Markov
./Markov
```

