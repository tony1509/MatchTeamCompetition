import itertools


teams = [0,1,2,3,4,5,6,7,8,9]
possible_combinations = []
contain_team_dict = {i: [] for i in range(10)}
contain_pair_dict = {}
label_combinations = {}
reverse_label_combinations = {}

for comb in itertools.combinations(teams, 4):
    possible_combinations.append(comb)

print(len(possible_combinations))

for i in range(len(possible_combinations)):
    label_combinations[possible_combinations[i]] = i
    reverse_label_combinations[i] = possible_combinations[i]

for i in range(10):
    for j in range(10):
        if i==j:
            continue
        contain_pair_dict['{}{}'.format(*sorted([i, j]))] = []

for i in range(10):
    for comb in possible_combinations:
        if i in comb:
            contain_team_dict[i].append(label_combinations[comb])

# with open('contain_team.txt', 'w+') as outfile:
#     for i in range(10):
#         outfile.write('{}\n'.format(contain_team_dict[i]))

for key, _ in contain_pair_dict.items():
    team_1 = int(key[0])
    team_2 = int(key[1])
    for comb in possible_combinations:
        if (team_1 in comb) and (team_2 in comb):
            contain_pair_dict[key].append(label_combinations[comb])

# with open('contain_pair.txt', 'w+') as outfile:
#     for key, val in contain_pair_dict.items():
#         outfile.write('{}\n'.format(val))

x = [0, 1, 18, 83, 84, 140, 179, 207, 208, 209]
for xi in x:
    print(reverse_label_combinations[xi])