package teste2018;

public class LogicVariable {
	
	String name;
	LogicGate calculatedBy = null;
	boolean value = false;
	
	public LogicVariable(String string, boolean value) {
		this.name = string;
		this.value = value;
	}

	public LogicVariable(String string) {
		this(string, false);
	}

	public String getName() {
		return name;
	}

	public boolean getValue() {
		if(calculatedBy == null) {
			return value;
		}
		else {
			return calculatedBy.evaluate();
		}
	}

	public void setValue(boolean b) {
		calculatedBy = null;
		value = b;
	}
	
	public boolean equals(Object o) {
		if(o instanceof LogicVariable) {
			LogicVariable v = (LogicVariable)o;
			return name == v.getName();
		}
		
		return false;
	}

	public LogicGate getCalculatedBy() {
		return calculatedBy;
	}

	public Object getFormula() {
		if(calculatedBy == null) {
			return name;
		}
		else {
			return calculatedBy.getFormula();
		}
	}
	
	public boolean checkUsed(LogicVariable v) {
		if(calculatedBy == null) {
			return false;
		}
		else {
			return calculatedBy.checkUsed(v);
		}
	}
}
