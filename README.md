# Puzzle
A sliding puzzle game in console

### Development
I used **Code::Blocks 17.12** as IDE and compiler on Windows 10.

### Features
You can easily change the size of the puzzle and console.

To change the size of console, just change the value in
```C
struct position_detail scr_size = {30, 120};        //MAX 255 as uint8_t is used....{height, width}
```

### Requisites
Function from [QBASIC-func-through-C](https://github.com/OjeshManandhar/QBASIC-func-through-C) and
[Basic-Function](https://github.com/OjeshManandhar/Basic-Functions) are used so make sure to install them.

### Installing/Cloning
To clone it on your local machine,
- Clone this repository to your local machine.
```shell
git clone https://github.com/OjeshManandhar/Puzzle
```
- Go inside the directory where you placed the cloned repo
- Make sure you have installed [QBASIC-func-through-C](https://github.com/OjeshManandhar/QBASIC-func-through-C) and
[Basic Function](https://github.com/OjeshManandhar/Basic-Functions)
- Compile and run the project *Puzzle.cbp*

### Further Improvements
If you're interested, feel free to fork and submit PR.
- Scoring system
- Calculating time taken to solve
- Better algorithm to shuffle the puzzle
- Interactive graphics
  
### License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
