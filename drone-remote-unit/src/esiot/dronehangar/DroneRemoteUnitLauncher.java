package esiot.dronehangar;

/**
 * Avvio del D.R.U.
 *
 * Uso:
 * java -cp bin:lib/jssc-2.9.4.jar esiot.dronehangar.DroneRemoteUnitLauncher
 * [porta]
 *
 * Se la porta non viene passata come argomento viene usato il valore di
 * default DEFAULT_PORT, da modificare in base al proprio sistema
 * (su Linux tipicamente /dev/ttyACM0 o /dev/ttyUSB0, su Windows COM3, etc...).
 */
public class DroneRemoteUnitLauncher {

	private static final String DEFAULT_PORT = "/dev/ttyUSB0";
	private static final int BAUD_RATE = 115200;

	public static void main(String[] args) throws Exception {
		String portName = (args.length >= 1) ? args[0] : DEFAULT_PORT;

		DroneRemoteUnitView view = new DroneRemoteUnitView();
		view.display();

		DroneRemoteUnitController controller = new DroneRemoteUnitController(portName, BAUD_RATE, view);
		view.registerController(controller);
	}
}