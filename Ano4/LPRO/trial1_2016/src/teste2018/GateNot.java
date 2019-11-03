package teste2018;

public class GateNot extends LogicGate {
	public GateNot(LogicVariable o, LogicVariable x1) throws ColisionException, CycleException {
		super(new LogicVariable[]{x1}, o, "NOT");
	}
	
	public boolean evaluate() {
		return !inputs[0].getValue();
	}
}
