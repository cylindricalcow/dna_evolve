# dna_evolve
Stochastic Evolution of DNA

Evolving the system

The goal of this project was to make a simple simulation of DNA evolution. It starts with a sequence of all 'A' nucleotides of length L. 
At every iteration, a random index in the sequence is chosen. Next, that index has two options: 1. transform into a different nucleotide 
2. Get deleted. At that point, another random index is chosen where a random nucleotide will attempt to be inserted. Evaluation of whether
or not a mutation will happen is done by calculating the energy of the old and new sequence. Bonds between A->T and G->C (and vice-versa)
have energy -1, bonds between X->X, for any X, have energy 0, and bonds between unfavorable pairs (e.g. A->G) have energy 1. Total energy
of a sequence is calculated by adding up the energy of all the pairs (smaller the better). After the energy calculation is done, 
Metropolis-Hastings algorithm is used to calculate if the mutation will happen i.e. alpha(c' -> c)=e^{-Beta*J*E_new}/e^{-Beta*J*E_new}, 
where J is the coupling constant and Beta=1/k_b*T. Alpha > 1 is automatically accepted. Alpha < 1 is accpeted with probability alpha.

Phase Transition

For Ising model systems, the phase transition can be found by calculating the average total magnetization density squared (m^2) at 
different temperatures for the system. The analog of magnetization for DNA nucleotides is a representation as a tuple. The first index is
for 'A'/'T' and the second is for 'G'/'C'. I used the convention 'A' and 'G' are positive 1 and 'T' and 'C' are negative. For example, 
'A'=[1,0] and 'C'=[0,-1]. So m^2 of the pair AC is ('A'+'C')^2 = [1,-1]^2 = [1,-1]*[1,-1] = 1^2 + (-1)^2 =2, while the m^2 of AT is 
('A'+'T')^2 = [1-1,0]^2=0. 
