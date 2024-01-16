STEPS FOR COMPILATION AND EXECUTION:

1. Create an environment variable with appropriate flags and libraries used in source code by copying the line below:
       
               FLAGS="$(pkg-config --cflags --libs opencv4)"

2. Open the current directory in terminal and compile the .cpp file using the command given below:

               g++ edgedetection.cpp -o cv $FLAGS

3. Execute the compiled cpp file by providing two arguments separated by space, first argument being the full path of test image and second   argument being the full path of json file containing parameters. 

            For example,
            ./cv /home/learn/Documents/cv/practice/projects/HoughP/0001.png /home/learn/Documents/cv/practice/projects/HoughP/.vscode/config.json

Above steps are tested on Ubuntu 18.04 and 20.04

               