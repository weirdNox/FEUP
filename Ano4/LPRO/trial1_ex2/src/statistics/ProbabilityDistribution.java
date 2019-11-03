package statistics;

public abstract class ProbabilityDistribution {
	double mean;
	double stdev;

	public ProbabilityDistribution(double d, double e) {
		if(e == 0) {
			throw new IllegalArgumentException();
		}
		mean = d;
		stdev = e;
	}

	public ProbabilityDistribution() {
		mean = 0;
		stdev = 1.0;
	}
	
	public double getMean() {
		return mean;
	}

	public double getStddev() {
		return stdev;
	}

	public abstract double probabilityDensityFunction(double d);

}
