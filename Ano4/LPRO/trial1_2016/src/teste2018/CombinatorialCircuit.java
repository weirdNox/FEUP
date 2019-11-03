package teste2018;

import java.util.TreeMap;

public class CombinatorialCircuit {
	TreeMap<String,LogicVariable> tree = new TreeMap<String,LogicVariable>();

	public boolean addVariable(LogicVariable a) {
		if(tree.containsKey(a.getName())) {
			return false;
		}
		
		tree.put(a.getName(), a);
		
		return true;
	}

	public LogicVariable getVariableByName(String string) {
		return tree.get(string);
	}

}
