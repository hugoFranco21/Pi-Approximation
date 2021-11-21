public class Nilikantha {
    private static final int SIZE = 1_000_000_000;
    private static final int N = 10;
    private double result;

    public Nilikantha(){}

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

    private double getResult(){
        return this.result;
    }

    public static void main(String args[]){
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