/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package frames;

import enums.TurnOnLight;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;
import java.awt.geom.RoundRectangle2D;
import javax.swing.JPanel;

/**
 *
 * @author Fito
 */
public class Semaforo extends JPanel{
    
    private TurnOnLight color = null;
    private int red[]   = { 130, 228, 0   };
    private int green[] = { 0,   228, 115 };
    private int blue[]  = { 0,   0,   0   };
    private Graphics2D graficas2d = null;
    private RoundRectangle2D borde = new RoundRectangle2D.Float();
    private Ellipse2D[] light = {
        
                                    new Ellipse2D.Float( 7.0f, 7.0f,  15.0f, 15.0f ),
                                    new Ellipse2D.Float( 7.0f, 25.0f, 15.0f, 15.0f ),
                                    new Ellipse2D.Float( 7.0f, 43.0f, 15.0f, 15.0f )
        
    };
    
    public Semaforo(int x, int y){
        
        borde.setFrame(0, 0, 29, 65);
        this.setBounds(x, y, 32, 67);
        this.setVisible(true);
        
    }
    
    public void powerOn(TurnOnLight color){
        
        switch(color){
            case RED:
                red[0] = 255;  green[0] = 0;   blue[0] = 0;       //Color Rojo
                red[1] = 229;  green[1] = 190; blue[1] = 1;       //Color Amarillo
                red[2] = 0;    green[2] = 115; blue[2] = 0;       //Color Verde
                break;
            case YELLOW:
                red[0] = 130;  green[0] = 0;   blue[0] = 0;       //Color Rojo
                red[1] = 255;  green[1] = 255; blue[1] = 0;       //Color Amarillo
                red[2] = 0;    green[2] = 115; blue[2] = 0;       //Color Verde
                break;
            case GREEN:
                red[0] = 130;  green[0] = 0;   blue[0] = 0;       //Color Rojo
                red[1] = 229;  green[1] = 190; blue[1] = 1;       //Color Amarillo
                red[2] = 0;    green[2] = 255; blue[2] = 0;       //Color Verde
                break;
        }
        this.color = color;
        repaint();
    }
    
    public TurnOnLight getTurnedOnLight()
    {
        return( this.color );
    }
    
    @Override
    public void paint( Graphics graphic )
    {
        graficas2d = ( Graphics2D ) graphic;
        graficas2d.setColor( new Color( 120, 120, 120 ) );
        graficas2d.fill( borde );
        draw( 0, red[0], green[0], blue[0] );
        draw( 1, red[1], green[1], blue[1] );
        draw( 2, red[2], green[2], blue[2] );
    }
    private void draw( int index, int red, int green, int blue )
    {
        graficas2d.setColor( new Color( red, green, blue ) );
        graficas2d.fill( light[index] );
    }
    
}
