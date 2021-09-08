
class Main extends Player {
	juice;
	babyJuice;

	constructor() {
		super( 1200, 800, "Hello world", false );
		this.scaleMode = ScaleMode.Pixel;
		this.displayMode = DisplayMode.Contain;
		this.letterboxColor = 0xff000000;
		this.backgroundColor = 0xff662222;

		this.juice = new display.Rive("juice.riv");
		this.juice.scaleX = 0.6;
		this.juice.scaleY = 0.6;
		this.juice.originX = this.juice.width / 2;
		this.juice.originY = this.juice.height / 2;
		this.juice.x = this.stage.width / 2;
		this.juice.y = this.stage.height / 2;
		//this.juice.hitArea = new geom.HitAreaCircle(540,540,540);
		this.stage.addChild( this.juice );

		this.babyJuice = new display.Rive( "juice.riv" );
		this.babyJuice.originX = this.babyJuice.width / 2;
		this.babyJuice.originY = this.babyJuice.height / 2;
		this.babyJuice.x = this.juice.width;
		this.babyJuice.y = 0;
		this.babyJuice.scaleX = 0.3;
		this.babyJuice.scaleY = 0.3;
		this.juice.addChild( this.babyJuice );

		console.log('About to listen');
		this.juice.listen( MouseEventType.Down, this.onMouseClick );
		this.stage.listen( PlayerEventType.Update, this.onUpdate );
		console.log('Done listening');

		console.log("Constructed");
	}

	onUpdate( t ) {
		console.log("onUpdate");
		console.log("  type: "+t.type);
		console.log("  cancelled: "+t.cancelled);
		//juice.rotation += event.dt * 20;
		//babyJuice.rotation += event.dt * 40;
		return true;
	}

	onMouseClick( t ) {
		console.log("onMouseClick");
		console.log("  type: "+t.type);
		console.log("  cancelled: "+t.cancelled);
		//babyJuice.x = juice.mouse.x;
		//babyJuice.y = juice.mouse.y;
		return false;
	}
}

main = new Main();
main.run();
