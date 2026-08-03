package esiot.dronehangar;

/**
 * Interfaccia per un canale di comunicazione asincrono a messaggi.
 */
public interface CommChannel {

	/**
	 * Invia un messaggio (stringa, senza newline finale).
	 * Comportamento asincrono.
	 */
	void sendMsg(String msg);

	/**
	 * Riceve un messaggio. Comportamento bloccante.
	 */
	String receiveMsg() throws InterruptedException;

	/**
	 * Controlla se un messaggio è disponibile.
	 */
	boolean isMsgAvailable();

}
