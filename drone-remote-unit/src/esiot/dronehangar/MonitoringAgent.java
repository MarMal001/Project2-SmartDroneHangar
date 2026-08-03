package esiot.dronehangar;

/**
 * Agente (thread dedicato) che riceve i messaggi dall'hangar e li fornisce
 * alla view a seconda del prefisso che gli identifica. (i Prefissi sono
 * definiti nella classe Protocol).
 */
public class MonitoringAgent extends Thread {

	private final SerialCommChannel channel;
	private final DroneRemoteUnitView view;

	private long lastStateLog = 0;

	public MonitoringAgent(SerialCommChannel channel, DroneRemoteUnitView view) {
		this.channel = channel;

		this.view = view;
	}

	public void run() {
		while (true) {
			try {
				String msg = channel.receiveMsg();

				if (msg.startsWith(Protocol.STATE_PREFIX)) {
					// log di debug, ma non ad ogni messaggio (arrivano ogni 500ms)
					long now = System.currentTimeMillis();
					if (now - lastStateLog > 2000) {
						lastStateLog = now;
						view.log("RX: " + msg);
					}
					handleState(msg.substring(Protocol.STATE_PREFIX.length()));
				} else if (msg.startsWith(Protocol.ALARM_PREFIX)) {
					view.log("ALARM segnalato dall'hangar");
				} else if (msg.startsWith(Protocol.LOG_PREFIX)) {
					view.log(msg.substring(Protocol.LOG_PREFIX.length()));
				} else if (!msg.isBlank()) {
					// messaggio non riconosciuto: lo mostro comunque nel log
					view.log("(raw) " + msg);
				}
			} catch (InterruptedException ex) {
				return;
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}

	private void handleState(String payload) {
		// formato atteso: <droneState>:<hangarState>:<distanceMm>
		String[] parts = payload.split(":");
		if (parts.length < 3) {
			view.log("Messaggio di stato malformato: " + payload);
			return;
		}
		try {
			String droneState = parts[0];
			String hangarState = parts[1];
			int distance = Integer.parseInt(parts[2]);
			view.updateState(droneState, hangarState, distance);
		} catch (NumberFormatException ex) {
			view.log("Distanza non valida nel messaggio di stato: " + payload);
		}
	}
}