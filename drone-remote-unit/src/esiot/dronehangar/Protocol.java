package esiot.dronehangar;

/**
 * Definizione del protocollo testuale scambiato via seriale tra
 * Arduino e questa applicazione (DRU).
 *
 * Ogni messaggio e' una singola riga (termina con '\n').
 *
 * --- Arduino -> DRU ---
 * st:<droneState>:<hangarState>:<distanceMm>
 * droneState puo essere | REST | TAKEOFF | OUT | LANDING
 * hangarState puo essere | NORMAL | PREALARM | ALARM
 * distanceCm è un intero (visibile solo durante LANDING)
 *
 * al:ALARM
 * inviato una tantum quando scatta l'allarme e il drone e' fuori
 *
 * lo:<testo>
 * messaggio di log/diagnostica da mostrare nella LogView
 *
 * --- DRU -> Arduino ---
 * cmd:OPEN
 * comando di apertura porta (simula sia il decollo che l'atterraggio, viene
 * ignorato in caso di allarme)
 */
public final class Protocol {

	private Protocol() {
	}

	public static final String STATE_PREFIX = "st:";
	public static final String ALARM_PREFIX = "al:";
	public static final String LOG_PREFIX = "lo:";

	public static final String CMD_OPEN = "cmd:OPEN";

	// drone states
	public static final String DRONE_REST = "REST";
	public static final String DRONE_TAKEOFF = "TAKEOFF";
	public static final String DRONE_OUT = "OUT";
	public static final String DRONE_LANDING = "LANDING";

	// hangar states
	public static final String HANGAR_NORMAL = "NORMAL";
	public static final String HANGAR_PREALARM = "PREALARM";
	public static final String HANGAR_ALARM = "ALARM";
}
