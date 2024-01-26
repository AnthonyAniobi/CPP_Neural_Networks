# Tests

Create test files and see how they perform on the neural networks
## Text Files available
**XOR Generator** 
A file that generates a list of random exclusive or inputs and outputs. 
The result of this file is saved in the `xor.csv`. 

To create this test file run the following command in the tests directory
```bash
g++ ./xor_generator.cpp -o ./xor_generator
./xor_generator > ./xor.csv
```