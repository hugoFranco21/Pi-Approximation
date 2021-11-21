/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje Java. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está paralelizado, utilizando la tecnología de Fork-Join
* Comando para compilar en Linux: javac NilikanthaThreads.java
* Comando para correr en Linux: java NilikanthaThreads
*--------------------------------------------------------------*/
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

public class NilikanthaForkJoin extends RecursiveTask<Double>{
    private static final int SIZE = 1_000_000_000;
    private static final int MIN = 100_000;
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
    public NilikanthaForkJoin(int start, int end) {
		this.start = start;
        this.end = end;
        this.result = 0;
	}

    /**
     * This function performs the calculation of the Nilikantha series from the value of start,
     * to the value of end, adding the calculation into the variable result.
     * @return Double
     */
    protected Double computeDirectly(){
        this.result = 0.0;
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
        return result;
    }
    
    /**
     * This function divides the amount of calculations into k processes of 
     * n calculations. After reaching the minimum threshold, it will call computeDirectly
     * which will perform the calculation. Until then it divides the amount of calculations by a 
     * factor of 2
     * @return Double
     */
    @Override
    protected Double compute() {
        if ( (end - start) <= MIN ) {
			return computeDirectly();
		} else {
			int mid = start + ( (end - start) / 2 );
			NilikanthaForkJoin lowerMid = new NilikanthaForkJoin(start, mid);
			lowerMid.fork();
			NilikanthaForkJoin upperMid = new NilikanthaForkJoin(mid, end);
			return upperMid.compute() + lowerMid.join();
		}
    }

    public static void main(String args[]){
        if(args.length >= 1){
            System.out.println("Error: No arguments are allowed");
            return;
        }
        long startTime, stopTime;
        double result = 0.0;
		double ms;
		ForkJoinPool pool;

		System.out.printf("Starting with %d threads...\n", MAXTHREADS);
		ms = 0;
		for (int i = 0; i < N; i++) {
			startTime = System.currentTimeMillis();
            /**
             * The number of threads assigned for the ForkJoin pool, is the maximum amount of
             * logical threads my machine has
             */
			pool = new ForkJoinPool(MAXTHREADS);
            /**
             * The line belows starts the calculation of the Nilikantha series
             * from 0 to the value of SIZE
             */
			result = pool.invoke(new NilikanthaForkJoin(0, SIZE));

			stopTime = System.currentTimeMillis();
			ms += (stopTime - startTime);
		}
		System.out.println("Pi is approx: " + result);
		System.out.println("Average time elapsed: " + (ms / N) + " ms");
    }

}