/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje Java. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está paralelizado, utilizando la tecnología de Java Threads.
* Comando para compilar en Linux: javac NilikanthaThreads.java
* Comando para correr en Linux: java NilikanthaThreads
*--------------------------------------------------------------*/
public class NilikanthaThreads extends Thread {
    private static final int SIZE = 1_000_000_000;
    public static final int MAXTHREADS = Runtime.getRuntime().availableProcessors();
    private static final int N = 10;
    private int start, end;
    private double result;

	/**
	 * Constructor for the NilikanthaThreads class. It will calculate the Nilikantha
	 * series from the start-term to the end-term and save the result to the variable
	 * "result"
	 * @param start int - Start point of the calculation
	 * @param end int - End point of the calculation
	 */
    public NilikanthaThreads(int start, int end) {
		this.start = start;
        this.end = end;
        this.result = 0;
	}

	/**
	 * This fuction implements the run function of the Thread class. Here, the 
	 * Nilikantha series going from start to end is calculated and saved to the class variable result.
	 */
	@Override
    public void run(){
        double sign, di, denominator, term;
        if(this.start == 0){
            this.result = 3.0;
            this.start++;
        }
        for(int i = start; i <= end; i++){
            sign = i % 2 == 0 ? -1.0 : 1.0;
            di = i*2.0;
            denominator = (di*(di+1)*(di+2));
            term = (4.0*sign)/denominator;
            this.result += term;
        }
    }

	/**
	 * Getter for the class variable result
	 * @return double
	 */
    private double getResult(){
        return this.result;
    }

    public static void main(String args[]){
		if(args.length >= 1){
            System.out.println("Error: No arguments are allowed");
            return;
        }
        long startTime, stopTime;
		int block;
		NilikanthaThreads threads[];
		double ms;
		double result = 0.0;

		/**
		 * block represents the amount of calculations each thread is going to process
		 */
		block = SIZE / MAXTHREADS;
		/**
		 * The number of threads created is the max my local 
		 * machine allows, which is 16. By doing this, you ensure you are using all the
		 * threads and not assigning extra work to an individual thread, or leaving threads
		 * without work to do.
		 */
		threads = new NilikanthaThreads[MAXTHREADS];

		System.out.printf("Starting with %d threads...\n", MAXTHREADS);
		ms = 0;
		for (int j = 1; j <= N; j++) {
			/**
			 * Threads are created and assigned their start and end values
			 */
			for (int i = 0; i < threads.length; i++) {
				if (i != threads.length - 1) {
					threads[i] = new NilikanthaThreads((i * block), ((i + 1) * block));
				} else {
					threads[i] = new NilikanthaThreads((i * block), SIZE);
				}
			}

			startTime = System.currentTimeMillis();
			/**
			 * The block below starts all the threads, this means it executes the
			 * run() method on every thread.
			 */
			for (int i = 0; i < threads.length; i++) {
				threads[i].start();
			}
			/** 
			 * The block below signals the main thread to wait for every individual thread to finish
			 */
			for (int i = 0; i < threads.length; i++) {
				try {
					threads[i].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			stopTime = System.currentTimeMillis();
			ms +=  (stopTime - startTime);
			/**
			 * In the last iteration, the result from every thread gets added to calculate
			 * the approximation
			 */
			if (j == N) {
				result = 0;
				for (int i = 0; i < threads.length; i++) {
					result += threads[i].getResult();
				}
			}
		}
		System.out.println("Pi is approx: " + result);
		System.out.println("Average time elapsed: " + (ms / N) + " ms");
    }
}