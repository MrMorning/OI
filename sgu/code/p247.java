import java.io.*;
import java.lang.*;
import java.util.StringTokenizer;
import java.math.*;

public class p247 implements Runnable {
    private void solve() throws IOException {
        //int n = nextInt();
		for(int p = 3; p < 1000; p += 2){
			System.out.println("Current Proceeding: " + Integer.toString(p));
			if(!isPrime(p))
				continue;
		//	int p = nextInt();
			BigInteger res = binomial(2 * p, p);
			BigInteger TWO = new BigInteger("2");
			res = res.subtract(TWO);
			BigInteger P = new BigInteger(Integer.toString(p));
			res = res.divide(P);
			res = res.add(TWO);
			writer.println("if (p == " + p + ") printf(\"" + res + "\");");
		}
    }

	private boolean isPrime(int x){
		int lim = (int)Math.sqrt((double)x);
		for(int t = 2; t <= lim; t ++)
			if(x % t == 0)
				return false;
		return true;
	}

	private BigInteger factorial(int n)
	{
		BigInteger res = BigInteger.ONE;
		for(int i = 1; i <= n; i ++)
			res = res.multiply(new BigInteger(Integer.toString(i)));
		return res;
	}

	private BigInteger binomial(int n, int k){
		BigInteger res = factorial(n);
		res = res.divide(factorial(k));
		res = res.divide(factorial(n - k));
		return res;
	}

    public static void main(String[] args) {
        new p247().run();
    }

    BufferedReader reader;
    StringTokenizer tokenizer;
    PrintWriter writer;

    public void run() {
        try {
            //reader = new BufferedReader(new InputStreamReader(System.in));
            reader = new BufferedReader(new FileReader("t.in"));
            tokenizer = null;
            //writer = new PrintWriter(System.out);
            writer = new PrintWriter("t.out");
            solve();
            reader.close();
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }
}
