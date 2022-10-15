import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*; 
import java.awt.*;
import java.awt.event.*; 
import java.util.*;
import java.awt.Color;
import java.awt.geom.GeneralPath;
import java.awt.Graphics2D;

public class java_final extends JFrame{

	JToggleButton tog1 = new JToggleButton("special_line");  
	JToggleButton tog2 = new JToggleButton("dotted_line");
	JToggleButton tog3 = new JToggleButton("ranbow_line");
	JToggleButton tog4 = new JToggleButton("star"); 
	JToggleButton tog5 = new JToggleButton("clear"); 
	JPanel jptog = new JPanel(new GridLayout(1, 2, 5, 5));
	JPanel jpspace = new JPanel();
    //JPanel jpall = new JPanel();
	private Container container;  
    private JPanel colorPanel; 
	Random ran = new Random();

	ButtonGroup togGroup = new ButtonGroup();

    int x1,x2,y1,y2,c3,x3,y3;
	
    int type;  
    int red;
    int green;
    int blue;
	int y=0;
	int z;
    

	ChangeListener cl = new ChangeListener(){

		public void stateChanged(ChangeEvent e){

			JToggleButton tb = (JToggleButton) e.getSource();
			String command = tb.getActionCommand();
			red=(int)(Math.random()*255);   
            green=(int)(Math.random()*255);
            blue=(int)(Math.random()*255);
            //update(g);
			if (command.equals("special_line")){
			   type = 1;
               addMouseListener(m1);
               addMouseMotionListener(m2);
			   
            }

			else if(command.equals("dotted_line")) {
			    type = 2;
                addMouseListener(m1);
                addMouseMotionListener(m2);
				
            }
			else if(command.equals("ranbow_line")) {
			    type = 3;
                addMouseListener(m1);
                addMouseMotionListener(m2);
            }
			
			else if(command.equals("star"))
			{
				type=4;
				addMouseListener(m1);
                addMouseMotionListener(m2);
				//addMouse(m3);
			}
			else if(command.equals("clear"))
			{
				type=5;
				repaint();
			}
		}
	};


    MouseListener m1 = new MouseListener(){
		public void mousePressed(MouseEvent e)
		{

					x1=e.getX();  
					y1=e.getY();   

		}
        public void mouseReleased(MouseEvent e){}
        public void mouseEntered(MouseEvent e){}
        public void mouseExited(MouseEvent e){}
		public void mouseClicked(MouseEvent e)
		{
				x3=e.getX();  
				y3=e.getY(); 
        }
    };
	
	


    MouseMotionListener m2 = new MouseMotionListener(){

        public void mouseDragged(MouseEvent e){
            Graphics g = getGraphics();

            x2=e.getX();  
            y2=e.getY(); 
			

            if(type == 1){
                g.setColor(new Color(red,green,blue)); 				
                g.drawLine(x1,y1,x2,y2); 
				y++;
				if(y==80)
				{
					x1=x2;  
                    y1=y2;  
					y=0;
				}
                
            }

            if (type == 2){
                 
                 g.setColor(new Color(red,green,blue));  
                 g.fillOval(x1,y1,5,5);
				 z++;
				 if(z%30==0)
				 {
					x1=x2;  
					y1=y2;
				 }					
             }
			 
			 if(type == 3){
                 
				Color cr = new Color(0,0,0);
				cr = new Color(ran.nextInt(256),ran.nextInt(256),ran.nextInt(256));
				g.setColor(cr);				
                g.drawLine(x1,y1,x2,y2); 
					x1=x2;  
                    y1=y2;  
                
            }
			if (type==4)
			{
				Graphics2D g2 = (Graphics2D) g; 
				GeneralPath drawstar = new GeneralPath();
				drawstar.moveTo(x3,y3);
				g2.setColor(new Color(red,green,blue)); 
				int s2x=x3-30;
				int s2y=y3+80;
				int s3x=x3+50;
				int s3y=y3+25;
				int s4x=x3-50;
				int s4y=y3+25;
				int s5x=x3+30;
				int s5y=y3+80;
				
				drawstar.lineTo(s2x,s2y);
				drawstar.lineTo(s3x,s3y);
				drawstar.lineTo(s4x,s4y);
				drawstar.lineTo(s5x,s5y);
				drawstar.closePath();
				g2.draw(drawstar);
				
			}
			
        }

        public void mouseMoved(MouseEvent e){}

    };


    public static void main(String args[]) {
		new javadraw1(); 
	}

	java_final(){

	    super("draw");
		container= getContentPane();
		colorPanel=new JPanel();
		
		JButton selectColorButton=new JButton("<html>choose<br>background</html>");
		selectColorButton.addActionListener(
		new ActionListener()
		{
			public void actionPerformed(ActionEvent event)
			{
				JColorChooser chooser=new JColorChooser();    
                Color color=chooser.showDialog(java_final.this,"<html>choose<br>background</html>",Color.lightGray ); 
                if (color==null)  
                {
					color=Color.white;  
				}
                   jpspace.setBackground(color);  
			}
		});
		
	    
		jptog.add(tog1); 
		jptog.add(tog2);
		jptog.add(tog3);
		jptog.add(tog4);
		jptog.add(tog5);

		togGroup.add(tog1);
		togGroup.add(tog2);
		togGroup.add(tog3);
		togGroup.add(tog4);
		togGroup.add(tog5);
		

		tog1.setActionCommand("special_line"); 
		tog2.setActionCommand("dotted_line");
		tog3.setActionCommand("ranbow_line");
		tog4.setActionCommand("star");
		tog5.setActionCommand("clear");

		tog1.addChangeListener(cl); 
		tog2.addChangeListener(cl);
		tog3.addChangeListener(cl);
		tog4.addChangeListener(cl);
		tog5.addChangeListener(cl);
		

		setLayout(new BorderLayout());
        add(jptog, BorderLayout.NORTH);
		container.add(selectColorButton,BorderLayout.EAST);
		container.add(colorPanel,BorderLayout.CENTER);
        add(jpspace, BorderLayout.CENTER);
        //setLayout(null);
       // jptog.setBounds(5,0,150,30);
	   // add(jptog);
	   // jpspace.setBounds(5,40,300,300);
	   // add(jpspace);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(350, 250);
		setVisible(true);
	}
}