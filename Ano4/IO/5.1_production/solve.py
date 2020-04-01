#!/usr/bin/env python
import common
import pulp

# NOTE(nox): Data
Profit = common.readArrayFromFile('profit.dat')
ProdHours = common.readMatrixFromFile('prod_hours.dat')
Capacity = common.readArrayFromFile('capacity.dat')
MaxHours = 200
MaxFactories = 2

# NOTE(nox): Indices
Typ = range(0, len(Profit))
Fac = range(0, len(Capacity))

# NOTE(nox): Decision variables
Quant = pulp.LpVariable.dicts('Quantity', [(T,F) for T in Typ for F in Fac], cat=pulp.LpInteger, lowBound=0)
Used = pulp.LpVariable.dicts('Factory used', Fac, cat=pulp.LpBinary)

# NOTE(nox): Objective function
Model = pulp.LpProblem('Profit', pulp.LpMaximize)
Model += sum(Quant[(T,F)]*Profit[T] for T in Typ for F in Fac)

# NOTE(nox): Subject to
Model += sum(Quant[(T,F)]*ProdHours[F][T] for T in Typ for F in Fac) <= MaxHours

Model += sum(Used[F] for F in Fac) <= MaxFactories

for F in Fac:
    Model += sum(Quant[(T,F)]*ProdHours[F][T] for T in Typ) <= Capacity[F]*Used[F]

# NOTE(nox): Solve
Status = Model.solve()

if Status == pulp.LpStatusOptimal:
  print(Model.objective.value())
  Model.writeLP('lp.out')
