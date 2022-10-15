import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class main_frame  {
    static JFrame jframe = new JFrame();
    static JFrame frame=new JFrame();
    static JFrame frame8=new JFrame();
    public static JPanel GImage = null;
    static JButton bnt = new JButton("4 * 4");

    static JButton bnt1 = new JButton("8 * 8");


    public main_frame() {
        initFrame();
    }
    private static void start_game4()
    {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame();
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.setTitle("Game of Fifteen");
            frame.setResizable(false);
            frame.add(new game(4, 550, 30), BorderLayout.CENTER);
            frame.pack();
            // center on the screen
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });

    }
        private static void start_game8 () {
            SwingUtilities.invokeLater(() -> {
                frame8 = new JFrame();
                frame8.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
                frame8.setTitle("Game of Fifteen");
                frame8.setResizable(false);
                frame8.add(new game(8, 550, 15), BorderLayout.CENTER);
                frame8.pack();
                // center on the screen
                frame8.setLocationRelativeTo(null);
                frame8.setVisible(true);
            });
        }


    // 初始化窗口
    public void initFrame() {
        // 利用JPanel添加背景图片

        GImage = new JPanel() {

            protected void paintComponent(Graphics g) {
                ImageIcon icon = new ImageIcon("C:\\Users\\owner\\OneDrive\\桌面\\java\\Final\\src\\main\\java\\111.png");
                Image img = icon.getImage();
                g.drawImage(img, 0, 0, icon.getIconWidth(),icon.getIconHeight(), icon.getImageObserver());
                jframe.setSize(icon.getIconWidth(), icon.getIconHeight());

            }

        };
        jframe.setTitle("puzzle game");
        jframe.add(GImage);
        jframe.pack();
        jframe.setVisible(true);
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    }


    public static void main(String[] args) {

        Container cp = jframe.getContentPane();
        bnt.setBounds(50, 70, 100, 70);
        cp.add(bnt);
        bnt1.setBounds(50, 210, 100, 70);
        cp.add(bnt1);
        new main_frame();
        bnt.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                start_game4();
            }
        });
        bnt1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                start_game8();
            }
        });




    }
}
