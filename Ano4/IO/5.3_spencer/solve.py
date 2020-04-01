#!/usr/bin/env python
import common
import pulp

# NOTE(nox): Data
Capacity = common.readArrayFromFile('capacity.dat')
Demand = common.readArrayFromFile('demand.dat')
DistCosts = common.readMatrixFromFile('distrib_costs.dat')
FixedCosts = common.readArrayFromFile('fixed_costs.dat')
ProdCosts = common.readArrayFromFile('prod_costs.dat')

# NOTE(nox): Indices
Fact = range(0, len(Capacity))
Cent = range(0, len(Demand))

# NOTE(nox): Decision variables
Dist = pulp.LpVariable.dicts('Distribution', [(F,C) for F in Fact for C in Cent], cat=pulp.LpInteger, lowBound=0)
Used = pulp.LpVariable.dicts('Factory used', [F for F in Fact], cat=pulp.LpBinary)

# NOTE(nox): Objective function
Model = pulp.LpProblem('Costs', pulp.LpMinimize)
Model += (sum(DistCosts[C][F]*Dist[(F,C)] for F in Fact for C in Cent) +
          sum(FixedCosts[F]*Used[F] for F in Fact) +
          sum(ProdCosts[F]*sum(Dist[(F,C)] for C in Cent) for F in Fact))

# NOTE(nox): Subject to
for F in Fact:
    Model += sum(Dist[(F,C)] for C in Cent) <= Capacity[F]*Used[F]

for C in Cent:
    Model += sum(Dist[(F,C)] for F in Fact) >= Demand[C]

Model += Used[0] == 1

# NOTE(nox): Solve
Status = Model.solve()

if Status == pulp.LpStatusOptimal:
  print(Model.objective.value())
  Model.writeLP('lp.out')
