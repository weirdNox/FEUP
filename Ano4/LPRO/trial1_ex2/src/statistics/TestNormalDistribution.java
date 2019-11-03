package statistics;

import static org.junit.Assert.*;
import org.junit.Test;


public class TestNormalDistribution {	
	// probablidade entre a m�dia e dois desvios padr�es ao lado
	private static final double prob2sigma = 0.477250; 	
	private static final double precision  = 5E-7;

	@Test
	public void testConstructor() {
		NormalDistribution n = new NormalDistribution(1.0, 3.0);
		assertEquals(1.0, n.getMean(), 0.0);
		assertEquals(3.0, n.getStddev(), 0.0);
	}

	@Test
	public void testDefaultConstructor() {
		NormalDistribution n = new NormalDistribution();
		assertEquals(0.0, n.getMean(), 0.0);
		assertEquals(1.0, n.getStddev(), 0.0);
	}
	
	@Test(expected = IllegalArgumentException.class)
	public void testInvallidStddev() {
		new NormalDistribution(0, 0);
	}

	@Test
	public void testProbabilityDistribution() {
		ProbabilityDistribution d = new NormalDistribution(0,1);
		assertEquals(0.0, d.getMean(), 0.0);
		assertEquals(1.0, d.getStddev(), 0.0);		
	}

	@Test
	public void testProbabilityDensityFunction() {
		// See formula in http://en.wikipedia.org/wiki/Normal_distribution 
		ProbabilityDistribution d = new NormalDistribution(0.0, 1.0);
		assertEquals(0.3989423, d.probabilityDensityFunction(0.0), precision);
		assertEquals(0.2419707, d.probabilityDensityFunction(1.0), precision);
		assertEquals(0.2419707, d.probabilityDensityFunction(-1.0), precision);
	}
//
//	@Test
//	public void testCalcRangeProbability() {
//		// calcRangeProbability(a,b) : probability of random variable 
//		// being in the interval [a, b]
//		ProbabilityDistribution n = new NormalDistribution(0, 1);
//		assertEquals(prob2sigma, n.calcRangeProbability(0, 2), precision);
//		assertEquals(prob2sigma, n.calcRangeProbability(-2, 0), precision);
//		assertEquals(2*prob2sigma, n.calcRangeProbability(-2, 2), precision);
//	}
//
//	@Test
//	public void testCalcLeftProbability() {
//		// calcLeftProbability(x) : probability of random variable <= x
//		ProbabilityDistribution n = new NormalDistribution(1, 1);
//		assertEquals(0.5, n.calcLeftProbability(1.0), precision);
//		assertEquals(0.5 + prob2sigma, n.calcLeftProbability(3.0), precision);
//		assertEquals(0.5 - prob2sigma, n.calcLeftProbability(-1.0), precision);
//	}
//
//	@Test
//	public void testEquals() {
//		NormalDistribution d1 = new NormalDistribution(0, 1);
//		NormalDistribution d2 = new NormalDistribution(0, 1);
//		assertNotSame(d1, d2);
//		assertEquals(d1, d2);
//	}
//	
//	@Test
//	public void testAsString() {
//		NormalDistribution d1 = new NormalDistribution(2.0, 5.0);
//		assertEquals("N(2.0, 5.0)", d1 + "");
//	}
//	
//	@Test
//	public void testFindDistribution() {
//		NormalDistribution X = new NormalDistribution("X", 2.0, 5.0);
//		NormalDistribution Y = new NormalDistribution("Y", 2.0, 5.0);
//		assertSame(X, ProbabilityDistribution.find("X"));
//		assertNull(ProbabilityDistribution.find("Z"));
//	}
}
