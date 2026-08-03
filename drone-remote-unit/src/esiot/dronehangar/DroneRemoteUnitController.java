package esiot.dronehangar;

public class DroneRemoteUnitController {

	private final SerialCommChannel channel;
	private final DroneRemoteUnitView view;

	public DroneRemoteUnitController(String port, int baudRate, DroneRemoteUnitView view) throws Exception {
		this.view = view;
		view.log("Apertura porta " + port + " e attesa riavvio Arduino...");
		channel = new SerialCommChannel(port, baudRate);
		new MonitoringAgent(channel, view).start();
		view.log("Pronto.");
	}

	public void sendOpenCommand() {
		view.log("TX: " + Protocol.CMD_OPEN);
		channel.sendMsg(Protocol.CMD_OPEN);
	}

	public void shutdown() {
		channel.close();
	}
}