/*----------------------------------------------------------------
* Multiprocesadores: Proyecto final
* Fecha: 21-Nov-2021
* Autor: A01654856 Hugo David Franco Ávila
* Descripción: Este código implementa la serie de Nilikantha para
    obtener una aproximación suficientemente precisa de Pi en el lenguaje Java. A medida
    que incrementan los términos de la serie, la aproximación es más precisa.
    El algoritmo está de forma secuencial.
* Comando para compilar en Linux: javac Nilikantha.java
* Comando para correr en Linux: java Nilikantha
*--------------------------------------------------------------*/
public class Nilikantha {
    private static final int SIZE = 1_000_000_000;
    private static final int N = 10;
    private double result;

    /**
     * Default constructor for the Nilikantha class
     */
    public Nilikantha(){}

    /**
     * This function receives an integer s, and calculates the Nilikantha series up to the s-term,
     * which represents an approximation to the term Pi. The larger the value of S, the better 
     * approximation you  get.
     * 
     * @param s int
     */
    public void calculate(int s){
        result = 3.0;
        double sign, di, denominator, term;
        for(int i = 1; i <= s; i++){
            sign = i % 2 == 0 ? -1.0 : 1.0;
            di = i*2.0;
            denominator = (di*(di+1)*(di+2));
            term = (4.0*sign)/denominator;
            result += term;
        }
    }

    /**
     * This function returns the value of result in the Nilikantha object
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
		double acum = 0;

		Nilikantha n = new Nilikantha();
		acum = 0;
		System.out.printf("Starting...\n");
		for (int i = 0; i < N; i++) {
			startTime = System.currentTimeMillis();

			n.calculate(SIZE);

			stopTime = System.currentTimeMillis();

			acum += (stopTime - startTime);
		}
		System.out.println("Pi is approx: " + n.getResult());
		System.out.println("Average time elapsed: " + (acum / N) + " ms");
    }
}