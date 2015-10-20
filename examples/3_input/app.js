/*
* 3ds.js
* Example 3 "Input"
* This example showcases input
*/

Console.init("TOP");
Console.clear(); //Clear the screen
print("Press B to exit the loop");
while(1){
    var input = Input.getInput();

    if(input.KEY_B)
        break;
	
	if(input.KEY)
		Console.print(JSON.stringify(input, null, 2));
}
