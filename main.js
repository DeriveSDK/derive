
class Main extends App {
	juice;

	constructor() {
		super(800, 880, "Hello world", false);

		this.juice = new display.Rive("juice.riv");
		this.juice.fit(this.stage.bounds, FitMode.Contain);
		this.stage.addChild(this.juice);
	}
}
main = new Main();
main.run();
