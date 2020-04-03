#!/usr/bin/env python
import common
import pulp

# NOTE(nox): Data
Proc = common.readMatrixFromFile('demand.dat')
Pv = common.readMatrixFromFile('selling_prices.dat')
Cf = common.readArrayFromFile('fixed_costs.dat')
Cv = common.readArrayFromFile('variable_costs.dat')
Cap = common.readArrayFromFile('capacity.dat')

# NOTE(nox): Indices
Mod = range(0, len(Pv))
Loj = range(0, len(Proc[0]))

# NOTE(nox): Decision variables
X = pulp.LpVariable.dicts('Number of watches', [(I,J) for I in Mod for J in Loj], cat=pulp.LpInteger, lowBound=0)
Y = pulp.LpVariable.dicts('Manufactured', Mod, cat=pulp.LpBinary)
Z = pulp.LpVariable.dicts('Sold in', [(I,J) for I in Mod for J in Loj], cat=pulp.LpBinary)

# NOTE(nox): Objective function
Model = pulp.LpProblem('Costs', pulp.LpMaximize)
Model += (sum(X[(I,J)]*(Pv[I][J] - Cv[I]) for I in Mod for J in Loj) -
          sum(Y[I]*Cf[I] for I in Mod))

# NOTE(nox): Subject to
for I in Mod:
    Model += Z[(I,0)] + Z[(I,1)] <= 1
    Model += Z[(I,2)] + Z[(I,3)] + Z[(I,4)] <= 1

    Model += sum(X[(I,J)] for J in Loj) <= Cap[I]*Y[I]
    Model += sum(X[(I,J)] for J in Loj) <= Cap[I]*Y[I]

    for J in Loj:
        Model += X[(I,J)] <= Proc[I][J]*Z[(I,J)]

Model += sum((sum(X[(I,J)] for J in Loj))/Cap[I] for I in Mod) <= 1

# NOTE(nox): Solve
Status = Model.solve()

if Status == pulp.LpStatusOptimal:
  print('Objective: {}'.format(Model.objective.value()))
  for I in Mod:
      print('Model {}'.format(I+1))
      for J in Loj:
          print('   Store {} -> {}'.format(J+1, X[(I,J)].value()))
  Model.writeLP('lp.out')
