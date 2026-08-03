package esiot.dronehangar;

import java.util.Date;
import javax.swing.*;

class LogView extends JFrame {

	private JTextArea log;

	public LogView() {
		super("Drone Hangar - Log");
		setSize(600, 400);
		setResizable(false);
		JPanel mainPanel = new JPanel();
		log = new JTextArea(24, 45);
		log.setEditable(false);
		JScrollPane scroll = new JScrollPane(log);
		mainPanel.add(scroll);
		this.getContentPane().add(mainPanel);
	}

	public void log(String msg) {
		SwingUtilities.invokeLater(() -> {
			String date = new Date().toString();
			log.append("[" + date + "] " + msg + "\n");
		});
	}

	public void display() {
		SwingUtilities.invokeLater(() -> this.setVisible(true));
	}
}
