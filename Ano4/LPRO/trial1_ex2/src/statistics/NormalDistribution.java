package statistics;

public class NormalDistribution extends ProbabilityDistribution {

	public NormalDistribution(double d, double e) {
		super(d, e);
	}

	public NormalDistribution() {
		super();
	}

	@Override
	public double probabilityDensityFunction(double d) {
		return 1/(stdev * Math.sqrt(Math.PI*2)) * Math.exp(-(d - mean)*(d - mean)/(2*stdev*stdev));
	}


}
