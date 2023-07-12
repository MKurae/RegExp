# RegExp
3rd assignment of the course Datastructures  
Last edit: 10 December 2022  

Regex String Matcher created by Luuk Daleman and Mirza Kuraesin

Upon launching the executable, a list of options appears for the user to type into the terminal.
First the user must type an expression before the other options can be used.

The 'print' command is more for debugging but we found it quite useful so we kept this.
In this, the states are displayed side by side. This is not sorted by state number, 
because then it is sometimes difficult to find the first state (e.g. in a * operation) and the states are in order of the count.
Eg exp 'ab':  

1 2 3 4 <------ state number     
------------       
a - b - <------ which letter it can accept  
2 3 4 0 <------ state it points to  
0 0 0 0 <------ other state it points to  

We chose this compact representation because we could quite easily reconstruct it with a tuple. 
recreate it. It is easy for the user to see how all the states are connected without
looking at a picture of the automaton itself, although this is also an option with the command dot.
For us, it was also an easy way to build the automaton with std::get.

Below, the automaton of '(bb|aa)*c*d' is shown in an image with GraphvizOnline:
https://dreampuf.github.io/GraphvizOnline/#digraph%20G%20%7B%0D%0Arankdir%3D%22LR%22%0D%0A%0911-%3E9%0D%0A%0911-%3E12%0D%0A%099-%3E1%0D%0A%099-%3E5%0D%0A%091-%3E2%20%5Blabel%3D%22b%22%5D%0D%0A%092-%3E3%0D%0A%093-%3E4%20%5Blabel%3D%22b%22%5D%0D%0A%094-%3E10%0D%0A%095-%3E6%20%5Blabel%3D%22a%22%5D%0D%0A%096-%3E7%0D%0A%097-%3E8%20%5Blabel%3D%22a%22%5D%0D%0A%098-%3E10%0D%0A%0910-%3E9%0D%0A%0910-%3E12%0D%0A%0912-%3E15%0D%0A%0915-%3E13%0D%0A%0915-%3E16%0D%0A%0913-%3E14%20%5Blabel%3D%22c%22%5D%0D%0A%0914-%3E13%0D%0A%0914-%3E16%0D%0A%0916-%3E17%0D%0A%0917-%3E18%20%5Blabel%3D%22d%22%5D%0D%0A%7D
