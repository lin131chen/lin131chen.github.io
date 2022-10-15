import javax.swing.*;
import java.awt.*;

public class Drawing {

    JFrame jframe = new JFrame();
    public static JPanel GImage = null;

    public Drawing() {
        initFrame();
    }

    // 初始化窗口
    public void initFrame() {
        // 利用JPanel添加背景图片

        GImage = new JPanel() {

            protected void paintComponent(Graphics g) {
                ImageIcon icon = new ImageIcon("src\\image\\111.jpg");
                Image img = icon.getImage();
                g.drawImage(img, 0, 0, icon.getIconWidth(),
                        icon.getIconHeight(), icon.getImageObserver());
                jframe.setSize(icon.getIconWidth(), icon.getIconHeight());

            }

        };
        jframe.add(GImage);
        jframe.pack();

    }

}