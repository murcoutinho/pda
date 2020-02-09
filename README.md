# Probabilistic Diffusion Analysis 

This project implements the technique presented in the paper "Probabilistic Diffusion Analysis" (PDA) which proposes a new technique that can be used to study, design, and cryptanalysis of cryptographic algorithms. PDA allows us to generalize cryptographic algorithms by transforming the discrete bits into probabilities such that the algorithm is generalized into a continuous mathematical function. 

We provide the source code for the Fundamental Probabilistic Cryptographic Operations (FPCO) library, which can be used to implement a wide range of cryptographic algorithms, in particular ARX or AND-RX algorithms, with continuous probabilistic operations. Using the FPCO library is possible to study the confusion and diffusion of cryptographic algorithms or implement metrics such as the Continuous Avalanche Factor (CAF) and the Magnitude Factor (MF), useful to measure the avalanche effect. 

The FPCO library is implemented in C, and a project in XCODE is available. It should be simple to compile the FPCO library in other platforms or operating systems. There is only one dependency to the library with is the relic-toolkit, available at: https://github.com/relic-toolkit

