import javax.swing.*;  
import java.awt.*;  
import java.awt.event.ActionEvent;  
import java.awt.event.ActionListener; 

public class testGame
{
	public static void main(String[] args)
	{
		MyGame mygame=new MyGame();
	}
}

class MyGame extends JFrame implements ActionListener
{
	JButton[] button;
	JButton restart;
	JLabel result;
	JPanel chessboard,basicPanel;
	boolean player=true;
	boolean Gameover=false;
	int chessnum=0;


MyGame()
{
	setTitle("OX_Game");
	setBounds(500,500,300,300);
	button=new JButton[10];
	restart=new JButton("Restart");
	chessboard=new JPanel();
	basicPanel=new JPanel();
	result=new JLabel("");
	chessboard.setLayout(new GridLayout(3,3));  
	basicPanel.setLayout(new FlowLayout());
	//chessboard.setBackground(Color.black);
	basicPanel.setBackground(Color.white);
	add(chessboard,BorderLayout.CENTER);  
	add(basicPanel,BorderLayout.SOUTH);  
	basicPanel.add(restart);  
	basicPanel.add(result);//布局设置  
	
	initchessboard();
	addChessboard(chessboard);
	restart.addActionListener(this);
	
	buttonListener();
	setVisible(true);
	setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	pack();	
}  

private void addChessboard(JPanel chessboard)
{
	for (int i=1;i<=9;i++)
	{
		chessboard.add(button[i]);
		button[i].setBackground(Color.black);
	}
}

private void initchessboard()
{
	for(int i=1;i<=9;i++)
	{
		button[i]=new JButton(""+i);
		button[i].setFont(new Font("Monaco", Font.BOLD, 0));
	}
}

private void buttonListener()
{ 
	for(int i=1;i<=9;i++)  
	{  
		button[i].addActionListener(this);  
	}  
}  

private void restartGame()
{
	chessboard.removeAll();
	chessboard.setLayout(new GridLayout(3,3));
	initchessboard();
	addChessboard(chessboard);
	buttonListener();
	chessboard.updateUI();  
	chessboard.repaint();  
	result.setText(" ");
	chessnum=0;
	Gameover=false; 
	player=true;
}
private boolean checkFull(int num)
{
	if (num==9)
	{
		return true;
	}
	return false;
}

private int checkWinner(int player,int num)
{
	if(num>=5)
	{
		char[] chess=new char[10];  
		for(int i=1;i<=9;i++)
		{  
			chess[i]=button[i].getLabel().charAt(0);  
		}  
		if((chess[1]==chess[2]&&chess[2]==chess[3])||  
		(chess[4]==chess[5]&&chess[5]==chess[6])||  
		(chess[7]==chess[8]&&chess[8]==chess[9])||  
		(chess[1]==chess[5]&&chess[5]==chess[9])||  
		(chess[3]==chess[5]&&chess[5]==chess[7])||  
		(chess[1]==chess[4]&&chess[4]==chess[7])||  
		(chess[2]==chess[5]&&chess[5]==chess[8])||  
		(chess[3]==chess[6]&&chess[6]==chess[9]) )
		{  
			return player;
		}		
		else if(checkFull(num))
		{
			return -1;
		}  
	}
	return -2;
	
}

@Override
public void actionPerformed(ActionEvent actionEvent) 
{
	int resultnum=-2;
	JButton buttonSource=(JButton)actionEvent.getSource();  
	if(buttonSource==restart)
	{   
		restartGame(); 
		return;		
	} 
	if(!Gameover)
	{
		String buttonMark=buttonSource.getLabel();
		/*if(buttonMark.equals(""))*/
		if(buttonMark.matches("[1-9]"))
		{
			if(player==true)
			{
				buttonSource.setLabel("O");
				buttonSource.setFont(new Font("Monaco", Font.BOLD, 80));
				buttonSource.setBackground(Color.black);
				//buttonSource.setBackground(black.control);
				buttonSource.setForeground(Color.white);
			}
			else
			{
				buttonSource.setLabel("X");
				buttonSource.setFont(new Font("Monaco", Font.BOLD, 80));
				buttonSource.setBackground(Color.black);
				buttonSource.setForeground(Color.white);
			}
			chessnum++;
			int now=player?0:1;
			resultnum=checkWinner(now,chessnum);
			if(resultnum==0)
		{
			result.setText("Player O win");
			result.setFont(new Font("Monaco", Font.BOLD, 20));
			Gameover=true;
		}
		else if(resultnum==1)
		{
			result.setText("Player X win");
			result.setFont(new Font("Monaco", Font.BOLD, 20));
			Gameover=true;
		}
		else if(resultnum==-1)
		{
			result.setText("No winner");
			result.setFont(new Font("Monaco", Font.BOLD, 20));
			Gameover=true;
		}
		else
			player=!player;
		}
	}
	return;
}
}
	
	
	
	
	