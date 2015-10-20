/*
* 3ds.js
* Example 3 "Input"
* This example showcases input
*/

print("Press B to exit the loop");
while(1){
    var input = Input.getInput();

    if(input.KEY_B)
        break;
	
	if(input.KEY)
		print(JSON.stringify(input, null, 2));
}
