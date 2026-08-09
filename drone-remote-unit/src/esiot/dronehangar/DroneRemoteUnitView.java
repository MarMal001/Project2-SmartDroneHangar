package esiot.dronehangar;

import java.awt.*;
import java.awt.event.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.text.DefaultCaret;

/**
 * GUI del Drone Remote Unit (DRU), in un'unica finestra.
 */
class DroneRemoteUnitView extends JFrame implements ActionListener {

	private static final Color BG = new Color(30, 33, 38);
	private static final Color PANEL_BG = new Color(42, 46, 53);
	private static final Color TEXT_LIGHT = new Color(230, 230, 235);
	private static final Color TEXT_DIM = new Color(160, 165, 175);
	private static final Color LOG_BG = new Color(24, 26, 30);
	private static final Color LOG_FG = new Color(210, 215, 220);

	private static final Color COL_NORMAL = new Color(76, 175, 100);
	private static final Color COL_PREALARM = new Color(230, 165, 45);
	private static final Color COL_ALARM = new Color(215, 70, 70);
	private static final Color COL_NEUTRAL = new Color(90, 130, 200);
	private static final Color COL_REST = new Color(110, 116, 128);

	private final SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm:ss");

	private Badge droneBadge;
	private Badge hangarBadge;
	private JLabel distanceValue;
	private JButton actionButton;
	private JTextArea logArea;
	private JPanel alarmBanner;

	private DroneRemoteUnitController controller;
	private String currentDroneState = Protocol.DRONE_REST;

	public DroneRemoteUnitView() {
		super("Smart Drone Hangar - Remote Unit");
		setSize(760, 640);
		setMinimumSize(new Dimension(560, 460));
		setLocationRelativeTo(null);

		getContentPane().setBackground(BG);
		getContentPane().setLayout(new BorderLayout(0, 0));

		JPanel top = new JPanel(new BorderLayout());
		top.setOpaque(false);
		top.add(buildHeader(), BorderLayout.NORTH);
		top.add(buildAlarmBanner(), BorderLayout.SOUTH);

		getContentPane().add(top, BorderLayout.NORTH);
		getContentPane().add(buildStatusAndControlPanel(), BorderLayout.CENTER);

		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent ev) {
				if (controller != null) {
					controller.shutdown();
				}
				System.exit(0);
			}
		});
	}

	// Components

	private JComponent buildHeader() {
		JPanel header = new JPanel(new BorderLayout());
		header.setBackground(BG);
		header.setBorder(new EmptyBorder(16, 20, 8, 20));

		JLabel title = new JLabel("Drone Remote Unit");
		title.setFont(new Font("SansSerif", Font.BOLD, 22));
		title.setForeground(TEXT_LIGHT);

		JLabel subtitle = new JLabel("Smart Drone Hangar - controllo remoto");
		subtitle.setFont(new Font("SansSerif", Font.PLAIN, 12));
		subtitle.setForeground(TEXT_DIM);

		JPanel titleBox = new JPanel();
		titleBox.setOpaque(false);
		titleBox.setLayout(new BoxLayout(titleBox, BoxLayout.Y_AXIS));
		titleBox.add(title);
		titleBox.add(subtitle);

		header.add(titleBox, BorderLayout.WEST);
		return header;
	}

	private JComponent buildAlarmBanner() {
		alarmBanner = new JPanel(new BorderLayout());
		alarmBanner.setBackground(COL_ALARM);
		alarmBanner.setBorder(new EmptyBorder(10, 20, 10, 20));
		alarmBanner.setVisible(false);

		JLabel text = new JLabel("ALARM - hangar bloccato, in attesa del reset dell'operatore");
		text.setFont(new Font("SansSerif", Font.BOLD, 13));
		text.setForeground(Color.WHITE);
		alarmBanner.add(text, BorderLayout.CENTER);

		return alarmBanner;
	}

	private JComponent buildStatusAndControlPanel() {
		JPanel wrapper = new JPanel(new BorderLayout(0, 14));
		wrapper.setOpaque(false);
		wrapper.setBorder(new EmptyBorder(0, 20, 20, 20));

		JPanel top = new JPanel();
		top.setOpaque(false);
		top.setLayout(new BoxLayout(top, BoxLayout.Y_AXIS));

		JPanel cards = new JPanel(new GridLayout(1, 3, 14, 0));
		cards.setOpaque(false);
		cards.setMaximumSize(new Dimension(Integer.MAX_VALUE, 110));

		droneBadge = new Badge("DRONE STATE", "REST", COL_REST);
		hangarBadge = new Badge("HANGAR STATE", "NORMAL", COL_NORMAL);

		JPanel distanceCard = new JPanel(new BorderLayout());
		distanceCard.setOpaque(true);
		distanceCard.setBackground(PANEL_BG);
		distanceCard.setBorder(new CompoundBorder(
				new LineBorder(new Color(60, 64, 72), 1, true),
				new EmptyBorder(12, 16, 12, 16)));
		JLabel distLabel = new JLabel("DISTANCE (mm)");
		distLabel.setFont(new Font("SansSerif", Font.BOLD, 11));
		distLabel.setForeground(TEXT_DIM);
		distanceValue = new JLabel("--");
		distanceValue.setFont(new Font("Monospaced", Font.BOLD, 26));
		distanceValue.setForeground(TEXT_LIGHT);
		distanceCard.add(distLabel, BorderLayout.NORTH);
		distanceCard.add(distanceValue, BorderLayout.CENTER);

		cards.add(droneBadge);
		cards.add(hangarBadge);
		cards.add(distanceCard);

		top.add(cards);
		top.add(Box.createRigidArea(new Dimension(0, 14)));

		JPanel buttonRow = new JPanel(new FlowLayout(FlowLayout.CENTER));
		buttonRow.setOpaque(false);
		actionButton = new JButton("Take Off");
		actionButton.setFont(new Font("SansSerif", Font.BOLD, 15));
		actionButton.setPreferredSize(new Dimension(180, 42));
		actionButton.setFocusPainted(false);
		actionButton.addActionListener(this);
		buttonRow.add(actionButton);
		top.add(buttonRow);

		wrapper.add(top, BorderLayout.NORTH);
		wrapper.add(buildLogPanel(), BorderLayout.CENTER);

		return wrapper;
	}

	private JComponent buildLogPanel() {
		JPanel panel = new JPanel(new BorderLayout(0, 6));
		panel.setOpaque(false);

		JLabel logTitle = new JLabel("LOG");
		logTitle.setFont(new Font("SansSerif", Font.BOLD, 11));
		logTitle.setForeground(TEXT_DIM);
		panel.add(logTitle, BorderLayout.NORTH);

		logArea = new JTextArea();
		logArea.setEditable(false);
		logArea.setLineWrap(true);
		logArea.setWrapStyleWord(true);
		logArea.setFont(new Font("Monospaced", Font.PLAIN, 13));
		logArea.setBackground(LOG_BG);
		logArea.setForeground(LOG_FG);
		logArea.setCaretColor(LOG_FG);
		logArea.setMargin(new Insets(10, 10, 10, 10));

		// Auto-Scrolling dei log
		DefaultCaret caret = (DefaultCaret) logArea.getCaret();
		caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);

		JScrollPane scroll = new JScrollPane(logArea,
				JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
				JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		scroll.setBorder(new LineBorder(new Color(60, 64, 72), 1, true));
		scroll.getVerticalScrollBar().setUnitIncrement(16);

		panel.add(scroll, BorderLayout.CENTER);
		return panel;
	}

	// API usata dal controller

	public void registerController(DroneRemoteUnitController controller) {
		this.controller = controller;
	}

	public void display() {
		SwingUtilities.invokeLater(() -> this.setVisible(true));
	}

	public void log(String msg) {
		SwingUtilities.invokeLater(() -> {
			logArea.append("[" + timeFormat.format(new Date()) + "] " + msg + "\n");
			logArea.setCaretPosition(logArea.getDocument().getLength());
		});
	}

	public void updateState(String droneState, String hangarState, int distance) {
		SwingUtilities.invokeLater(() -> {
			currentDroneState = droneState;

			droneBadge.setValue(droneState, colorForDroneState(droneState));
			hangarBadge.setValue(hangarState, colorForHangarState(hangarState));
			alarmBanner.setVisible(Protocol.HANGAR_ALARM.equals(hangarState));

			if (Protocol.DRONE_LANDING.equals(droneState) || Protocol.DRONE_TAKEOFF.equals(droneState)) {
				distanceValue.setText(String.valueOf(distance));
			} else {
				distanceValue.setText("--");
			}

			updateButton();
		});
	}

	// Utility

	private Color colorForHangarState(String hangarState) {
		switch (hangarState) {
			case Protocol.HANGAR_ALARM:
				return COL_ALARM;
			case Protocol.HANGAR_PREALARM:
				return COL_PREALARM;
			default:
				return COL_NORMAL;
		}
	}

	private Color colorForDroneState(String droneState) {
		switch (droneState) {
			case Protocol.DRONE_REST:
				return COL_REST;
			case Protocol.DRONE_OUT:
				return new Color(120, 100, 190);
			default: // TAKEOFF / LANDING
				return COL_NEUTRAL;
		}
	}

	private void updateButton() {
		if (Protocol.DRONE_REST.equals(currentDroneState)) {
			actionButton.setText("Take Off");
			actionButton.setEnabled(true);
		} else if (Protocol.DRONE_OUT.equals(currentDroneState)) {
			actionButton.setText("Land");
			actionButton.setEnabled(true);
		} else {
			// TAKEOFF o LANDING gia' in corso, nessuna nuova richiesta possibile
			actionButton.setEnabled(false);
		}
	}

	@Override
	public void actionPerformed(ActionEvent ev) {
		if (ev.getSource() == actionButton && controller != null) {
			controller.sendOpenCommand();
		}
	}

	// Badge degli stati

	private static class Badge extends JPanel {
		private final JLabel valueLabel;
		private final JLabel titleLabel;
		private Color accent;

		Badge(String title, String initialValue, Color initialAccent) {
			this.accent = initialAccent;
			setOpaque(false);
			setLayout(new BorderLayout());
			setBorder(new EmptyBorder(12, 16, 12, 16));

			titleLabel = new JLabel(title);
			titleLabel.setFont(new Font("SansSerif", Font.BOLD, 11));
			titleLabel.setForeground(TEXT_DIM);

			valueLabel = new JLabel(initialValue);
			valueLabel.setFont(new Font("SansSerif", Font.BOLD, 22));
			valueLabel.setForeground(Color.WHITE);

			add(titleLabel, BorderLayout.NORTH);
			add(valueLabel, BorderLayout.CENTER);
		}

		void setValue(String value, Color accent) {
			this.accent = accent;
			valueLabel.setText(value);
			repaint();
		}

		@Override
		protected void paintComponent(Graphics g) {
			Graphics2D g2 = (Graphics2D) g.create();
			g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
			g2.setColor(accent.darker());
			g2.fillRoundRect(0, 0, getWidth(), getHeight(), 14, 14);
			g2.setColor(blend(accent, PANEL_BG, 0.55));
			g2.fillRoundRect(2, 2, getWidth() - 4, getHeight() - 4, 12, 12);
			g2.dispose();
			super.paintComponent(g);
		}

		private static Color blend(Color a, Color b, double ratio) {
			int r = (int) (a.getRed() * ratio + b.getRed() * (1 - ratio));
			int g = (int) (a.getGreen() * ratio + b.getGreen() * (1 - ratio));
			int bl = (int) (a.getBlue() * ratio + b.getBlue() * (1 - ratio));
			return new Color(r, g, bl);
		}
	}
}