/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package classes;

import enums.TurnOnLight;
import frames.Semaforo;
import java.util.List;

/**
 *
 * @author Fito
 */
public class CoordinadorSemaforo extends Thread{
    
    private boolean stop = false;
    private List<Semaforo> semaforos = null;
    
    
    public CoordinadorSemaforo(List<Semaforo> semaforos){
        this.semaforos = semaforos;
    }
    
    public void terminate(){
        this.stop = true;
    }
    
    @Override
    public void run()
    {
        try
        {
            int active = 0;
            boolean[] go = new boolean[semaforos.size()];
            for( int i = 0; i < go.length; i++ )
            {
                go[i] = false;
            }
            go[0] = true;
            while( !this.stop )
            {
                for( int i = 0; i < go.length; i++ )
                {
                    if( !go[i] )
                    {
                        semaforos.get( i ).powerOn( TurnOnLight.RED );
                    }
                    else
                    {
                        semaforos.get( i ).powerOn( TurnOnLight.GREEN );
                        active = i;
                    }
                }
                sleep( 5000 );
                semaforos.get( active ).powerOn( TurnOnLight.YELLOW );
                sleep( 2000 );
                go[active] = false;
                active++;
                if( active == semaforos.size() )
                {
                    active = 0;
                }
                go[active] = true;
            }
        }
        catch( InterruptedException e )
        {
            e.printStackTrace();
        }
    }
    
}
