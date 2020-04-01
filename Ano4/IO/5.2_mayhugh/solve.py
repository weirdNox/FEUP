#!/usr/bin/env python
import common
import pulp

# NOTE(nox): Data
AvailHours = common.readArrayFromFile('avail_hours.dat')
Demand = common.readArrayFromFile('demand.dat')
ProdHours = common.readMatrixFromFile('prod_hours.dat')
ProdMin = common.readArrayFromFile('prod_min.dat')
Profit = common.readArrayFromFile('profit.dat')
SalesCosts = common.readArrayFromFile('sales_costs.dat')

# NOTE(nox): Indices
Fam = range(0, len(Profit))
Sec = range(0, len(ProdHours))

# NOTE(nox): Decision variables
Quant = pulp.LpVariable.dicts('Quantity', Fam, cat=pulp.LpContinuous, lowBound=0)
Sales = pulp.LpVariable.dicts('Has sales', Fam, cat=pulp.LpBinary)

# NOTE(nox): Objective function
Model = pulp.LpProblem('Profit', pulp.LpMaximize)
Model += sum(Quant[F]*Profit[F] for F in Fam) - sum(Sales[F]*SalesCosts[F] for F in Fam)

# NOTE(nox): Subject to
for S in Sec:
    Model += sum(Quant[F]*ProdHours[S][F] for F in Fam) <= AvailHours[S]

for F in Fam:
    Model += Quant[F] >= Sales[F]*ProdMin[F]
    Model += Quant[F] <= Sales[F]*Demand[F]

# NOTE(nox): Solve
Status = Model.solve()

if Status == pulp.LpStatusOptimal:
  print(Model.objective.value())
  Model.writeLP('lp.out')
