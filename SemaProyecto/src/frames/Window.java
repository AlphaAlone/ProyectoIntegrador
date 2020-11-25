/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package frames;

import classes.CoordinadorSemaforo;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JFrame;

/**
 *
 * @author Fito
 */
public class Window extends JFrame{
    
    private CoordinadorSemaforo coordinator = null;
    private List<Semaforo> semafoross = new ArrayList<Semaforo>();
    public Window()
    {
        semafoross.add( new Semaforo( 50, 10 ) );
        semafoross.add( new Semaforo( 400, 10 ) );
        semafoross.add( new Semaforo( 50, 160 ) );
        semafoross.add( new Semaforo( 400, 160 ) );
        coordinator = new CoordinadorSemaforo( semafoross );
        this.setLayout( null );
        this.setBounds( 200, 100, 500, 300 );
        //semaphores.add( new Semaforo( ( this.getWidth() - 32 ) / 2, ( this.getHeight() - 67 ) / 2 ) );
        this.setVisible( true );
    }
    public void start()
    {
        for( Semaforo semaphore : semafoross )
        {
            this.getContentPane().add( semaphore );
        }
        this.addWindowListener(
            new WindowAdapter()
            {
                @Override
                public void windowOpened( WindowEvent e )
                {
                    coordinator.start();
                }
                @Override
                public void windowClosing( WindowEvent e )
                {
                    coordinator.terminate();
                    coordinator = null;
                    dispose();
                }
            }
        );
    }
    
}
