package teste2018;

import static org.junit.Assert.*;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.Arrays;

import org.junit.Test;

public class TestLogicCircuits {
	// auxiliary method
	private void fieldsArentPublic(Class<?> ... classes) {
		for (Class<?> c: classes)
			for (Field f : c.getDeclaredFields())
				assertFalse(Modifier.isPublic(f.getModifiers()));
	}
	
	private void isAbstract(Class<?> c) {
		assertTrue(Modifier.isAbstract(c.getModifiers()));
	}
		
    // test methods
	
	@Test
	public void testLogicVariable() {
		LogicVariable X1 = new LogicVariable("X1", false);
		assertEquals("X1", X1.getName());
		assertEquals(false, X1.getValue());
		X1.setValue(true);
		assertEquals(true, X1.getValue());
		fieldsArentPublic(LogicVariable.class);	
	}

	
	@Test
	public void testEquals() {
		LogicVariable a = new LogicVariable("Y1");
		LogicVariable b = new LogicVariable("Y1");
		assertTrue(a.equals(b)); // same name
		assertTrue(a.equals((Object)b));		
	}	
	

	@Test
	public void testLogicGates() throws Exception {
		LogicVariable X1 = new LogicVariable("X1", false); // input variable
		LogicVariable X2 = new LogicVariable("X2", false); // input variable
		LogicVariable X3 = new LogicVariable("X3", false); // input variable
		LogicVariable W1 = new LogicVariable("W1"); // 'internal' variable
		LogicVariable W2 = new LogicVariable("W2"); // 'internal' variable
		LogicVariable Y1 = new LogicVariable("Y1"); // output variable
		
		LogicGate p1 = new GateAnd(W1, X1, X2);
		assertSame(W1, p1.getOutput());
		assertTrue(Arrays.equals(new LogicVariable[]{X1, X2}, p1.getInputs()));
		
		LogicGate p2 = new GateOr(W2, W1, X3);
		assertSame(W2, p2.getOutput());
		assertTrue(Arrays.equals(new LogicVariable[]{W1, X3}, p2.getInputs()));
		
		LogicGate p3 = new GateNot(Y1, W2);
		assertSame(Y1, p3.getOutput());
		assertTrue(Arrays.equals(new LogicVariable[]{W2}, p3.getInputs()));	
		
		fieldsArentPublic(LogicGate.class, GateAnd.class, GateOr.class, GateNot.class);
		isAbstract(LogicGate.class);
	}

	@Test
	public void testSymbols() throws Exception {
		LogicVariable X1 = new LogicVariable("X1", false);
		LogicVariable X2 = new LogicVariable("X2", false);
		LogicVariable X3 = new LogicVariable("X3", false);
		LogicVariable W1 = new LogicVariable("W1");
		LogicVariable W2 = new LogicVariable("W2");
		LogicVariable Y1 = new LogicVariable("Y1");
		
		LogicGate p1 = new GateAnd(W1, X1, X2);
		assertEquals("AND", p1.getSymbol());
		
		LogicGate p2 = new GateOr(W2, W1, X3);
		assertEquals("OR", p2.getSymbol());
		
		LogicGate p3 = new GateNot(Y1, W2);
		assertEquals("NOT", p3.getSymbol());
		
		fieldsArentPublic(LogicGate.class, GateAnd.class, GateOr.class, GateNot.class);
		isAbstract(LogicGate.class);
	}

	@Test
	public void testCalculatedVariables() throws Exception {
		LogicVariable X1 = new LogicVariable("X1", false);
		LogicVariable X2 = new LogicVariable("X2", false);
		LogicVariable Y1 = new LogicVariable("Y1");

		LogicGate p1 = new GateAnd(Y1, X1, X2);

		assertSame(null, X1.getCalculatedBy());
		assertSame(null, X2.getCalculatedBy());
		assertSame(p1, Y1.getCalculatedBy());
	}

	// A variable cannot be the output of multiple gates
	@Test(expected = ColisionException.class)
	public void testColision() throws Exception {
		LogicVariable X1 = new LogicVariable("X1", false);
		LogicVariable X2 = new LogicVariable("X2", false);
		LogicVariable X3 = new LogicVariable("X3", false);
		LogicVariable X4 = new LogicVariable("X4", false);
		LogicVariable Y1 = new LogicVariable("Y1");

		LogicGate p1 = new GateAnd(Y1, X1, X2);
		LogicGate p2 = new GateOr(Y1, X3, X4);
	}

	@Test
	public void testFormulas() throws Exception {
		LogicVariable X1 = new LogicVariable("X1", false);
		LogicVariable X2 = new LogicVariable("X2", false);
		LogicVariable X3 = new LogicVariable("X3", false);
		LogicVariable W1 = new LogicVariable("W1");
		LogicVariable W2 = new LogicVariable("W2");
		LogicVariable Y1 = new LogicVariable("Y1");
		
		LogicGate p1 = new GateAnd(W1, X1, X2);
		LogicGate p2 = new GateOr(W2, W1, X3);
		LogicGate p3 = new GateNot(Y1, W2);
		
		assertEquals("X1", X1.getFormula());
		assertEquals("NOT(OR(AND(X1,X2),X3))", Y1.getFormula());
		assertEquals("NOT(OR(AND(X1,X2),X3))", p3.getFormula());
	}
	
	@Test
	public void testValues() throws Exception {
		LogicVariable X1 = new LogicVariable("X1", false);
		LogicVariable X2 = new LogicVariable("X2", true);
		LogicVariable X3 = new LogicVariable("X3", true);
		LogicVariable W1 = new LogicVariable("W1");
		LogicVariable W2 = new LogicVariable("W2");
		LogicVariable Y1 = new LogicVariable("Y1");
		
		LogicGate p1 = new GateAnd(W1, X1, X2);
		LogicGate p2 = new GateOr(W2, W1, X3);
		LogicGate p3 = new GateNot(Y1, W2);
		
		assertEquals(false, X1.getValue());
		assertEquals(true, X2.getValue());
		assertEquals(true, X3.getValue());
		assertEquals(false, W1.getValue());
		assertEquals(true, W2.getValue());
		assertEquals(false, Y1.getValue());
		
		X3.setValue(false);
		assertEquals(true, Y1.getValue());
	}
	
	// Circular dependencies are not allowed
	@Test(expected = CycleException.class)
	public void testCycles() throws Exception {
		LogicVariable W1 = new LogicVariable("W1");
		LogicVariable W2 = new LogicVariable("W2");
		LogicVariable w3 = new LogicVariable("W3");
		
		LogicGate p1 = new GateAnd(w3, W2, W1);
		LogicGate p2 = new GateNot(W2, w3);		
	}

	@Test
	public void testCombinatorialCircuit() {
		CombinatorialCircuit c = new CombinatorialCircuit();
		LogicVariable a = new LogicVariable("X1");
		LogicVariable b = new LogicVariable("X1");
		assertEquals(true, c.addVariable(a));
		assertEquals(false, c.addVariable(b)); // duplicate names not allowed
		assertSame(a, c.getVariableByName("X1"));
		assertSame(null, c.getVariableByName("X2"));
	}
}