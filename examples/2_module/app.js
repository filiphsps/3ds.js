/*
* 3ds.js
* Example 2 "Modules"
* This example showcases how to use modules
*/

Console.init("top");
Console.clear(); //Clear the screen
Console.print("\x1b[0;0H"); //Clear the screen
Console.print("Hello World from app.js");

var lib = require('library');
lib.hello(lib.world);

while(1) {
    var input = Input.getInput();
    if(input.KEY_A)
        break;
    Console.flushBuffers();
}
