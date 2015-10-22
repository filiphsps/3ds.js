/*
* 3ds.js
* Example 1 "Simple"
* This example showcases a benchmarking
*/

Console.init("top");
Console.clear(); //Clear the screen
Console.print("3ds.js version: " + System.version + "\n");
Console.print("duktape version: " + Duktape.version + "\n");
while(1) {
    var input = Input.getInput();
    if(input.KEY_A)
        break;
    Console.flushBuffers();
}
