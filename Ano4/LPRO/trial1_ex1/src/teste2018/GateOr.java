package teste2018;

public class GateOr extends LogicGate {
	public GateOr(LogicVariable o, LogicVariable x1, LogicVariable x2) throws ColisionException, CycleException {
		super(new LogicVariable[]{x1, x2}, o, "OR");
	}

	public boolean evaluate() {
		return inputs[0].getValue() || inputs[1].getValue();
	}
}
