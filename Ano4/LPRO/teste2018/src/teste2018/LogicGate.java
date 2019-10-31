package teste2018;


public abstract class LogicGate {
	LogicVariable[] inputs;
	LogicVariable   output;
	String symbol;
	
	public LogicGate(LogicVariable[] inputs, LogicVariable output, String sym) throws ColisionException, CycleException {
		this.inputs = inputs;
		this.output = output;
		if(checkUsed(output)) {
			throw new CycleException();
		}
		if(output.calculatedBy == null) {
			output.calculatedBy = this;
		}
		else {
			throw new ColisionException();
		}
		symbol = sym;
	}

	public LogicVariable getOutput() {
		return output;
	}

	public LogicVariable[] getInputs() {
		return inputs;
	}

	public Object getFormula() {
		String result = symbol + "(";
		boolean comma = false;
		for(LogicVariable in : inputs) {
			if(comma) {
				result += ",";
			}
			result += in.getFormula();
			comma = true;
		}
		result += ")";
		
		return result;
	}


	public String getSymbol() {
		return symbol;
	}
	
	public abstract boolean evaluate();

	public boolean checkUsed(LogicVariable v) {
		for(LogicVariable in : inputs) {
			if(in.equals(v) || in.checkUsed(v)) {
				return true;
			}
		}
		return false;
	} 
}
