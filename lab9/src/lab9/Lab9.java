/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab9;

import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;


/**
 *
 * @author Bezalel Benoy
 */
public class Lab9 {

    static int philosopher = 6;
    static philosopher philosophers[] = new philosopher[philosopher];
    static fork forks[] = new fork[philosopher];
    
    static class fork{
        
        public Semaphore mutex = new Semaphore(1);
        
        void grab(){
            try{
                mutex.acquire();
            }
            catch(Exception e){
                e.printStackTrace(System.out);
            }
            
        }
        void release(){
            mutex.release();
        }
        boolean isReleased(){
            return mutex.availablePermits()>0;
        }
    }
    static class philosopher extends Thread {
    
    public int number;
    public fork leftfork;
    public fork rightfork;
    
    philosopher(int num, fork left, fork right){
        number= num;
        leftfork = left;
        rightfork= right;
    }
    
    public void run(){
        
       while(true){
           leftfork.grab();
           System.out.println("Philosopher"+(number+1)+" grabs left fork");
           rightfork.grab();
           System.out.println("Philospher"+(number+1)+" grabs right fork");
           eat();
           leftfork.release();
           System.out.println("Philospher"+(number+1)+" releases left fork");
           rightfork.release();
           System.out.println("Philospher"+(number+1)+" releases right fork");
           
       }
    }
    void eat(){
        try{
            int sleepTime= ThreadLocalRandom.current().nextInt(0,1000);
            System.out.println("Philosopher"+(number+1)+"eats for"+sleepTime);
            Thread.sleep(sleepTime);
        }
        catch(Exception e){
            e.printStackTrace(System.out);
        }
    }
}
public static void main(String argv[]){
    for(int i=0; i<philosopher;i++){
        forks[i] = new fork();
    }
    
    for(int i = 0; i<philosopher;i++){
        philosophers[i]= new philosopher(i,forks[i],forks[(i+1)%philosopher]);
        philosophers[i].start();
}
    while(true){
        try{
            Thread.sleep(1000);
            
            boolean deadlock = true;
            for (fork f: forks){
                if(f.isReleased()){
                    deadlock=false;
                    break;
                }
            }
            if(deadlock){
                Thread.sleep(1000);
                System.out.println("All Philosophers Have Eaten Dinner");
                break;
            }
        }
        catch(Exception e){
            e.printStackTrace(System.out);
        }
    }
    System.out.println("Exit Program");
    System.exit(0);
}
}
//Still not working properly