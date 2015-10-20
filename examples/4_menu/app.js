/*
* 3ds.js
* Example 4 "Menu"
* This example showcases more advanced use of the runtime
*/

var running = true;
main();
function main() {
	Console.init("bottom");
	
	//Draw Menu
	menu([
		{
			title: "Survey",
			renderer: function () {
				var items = ['Yes', 'No', 'Maybe', 'I plan to'],
					position = 0;
				while(1) {
					var input = Input.getInput();
					if(input.KEY_A) {
						break;
					} else if(input.KEY_RIGHT) {
						position = (position + 1) <= (items.length - 1) ? (position + 1) : 0;
					} else if(input.KEY_LEFT) {
						position = (position - 1) >= 0 ? (position - 1) : (items.length - 1);
					}
					
					Console.clear();
					Console.print("\n\n  Survey\n\n\n\n");
					Console.print("  Have you tried Playstr.link?\n");
					Console.print("  < " + items[position] + " >\n");
					Console.flushBuffers();
				}
			},
		},
		{
			title: "Random menu entry",
			renderer: function () {
				var items = ['Yes', 'No', 'Maybe', 'I plan to'],
					position = 0;
				while(1) {
					var input = Input.getInput();
					if(input.KEY_B) {
						break;
					}
					
					Console.clear();
					Console.print("\n\n  Random menu entry\n\n\n\n");
					Console.print("  Hello World\n");
					Console.print("  Press B to go back\n");
					Console.flushBuffers();
				}
			},
		},
		{
			title: "Exit",
			renderer: function () {
				running = false;
			},
		},
	]);
}

function menu(items) {
	var position = 0;
	while(running){
		var input = Input.getInput();
		if(input.KEY_A) {
			items[position].renderer();
		} else if(input.KEY_DOWN) {
			position = (position + 1) <= (items.length - 1) ? (position + 1) : 0;
		} else if(input.KEY_UP) {
			position = (position - 1) >= 0 ? (position - 1) : (items.length - 1);
		}
		
		Console.clear();
		Console.print("\n\n  3ds.js Menu Example\n\n\n\n");
		for(var x = 0; x < items.length; x++){
			var item = items[x];
			Console.print((position == x ? " >" : "  ") + item.title + "\n");
		}
		Console.flushBuffers();
	}
}