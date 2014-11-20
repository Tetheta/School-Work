/*
Program file name : Travis.Crumley.cpp		OS: Windows 8          		Assignment # : 5
Programmer : Travis Crumley				    Class : CPTR 143			Date : 5/12/2014
Compiler : Visual Studio 2013

Assistance / references :
Lectures posted on common drive(K : \common)
PDFs in Reading folder of K drive

Description : A C++ Program that creates a Minimal Perfect Hashing Function, 
via preprocessed words and a backtracking procedure.

Inputs : None, words I'm hashing for are hard coded
Outputs : End value of all letters and the hash numbers for each word

Special Comments : Initialized my arrays to very large numbers because I
wasn't sure initially how far to initialize them and for the purpose of
this program that small gain in execution time matters very little.

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~
Assignment Requirements ___ / 3.0
Code Format / Cosmetics ___ / 3.0
Header & Code Comments : ___ / 2.0
Output Format / Cosmetics ___ / 2.0

***Does Not Compile*** : ___(-10.0)
***Late Work Deduction*** : ___(-0.5 / day)
Total Grade : ___ / 10.0

*****************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int value[1000];

int len;

inline int myHash(const string word)
{
	len = word.length();
	return len + value[word[0]] + value[word[len - 1]];
}

int main()
{
	//Initializations
	bool exists[1000];
	for (int i = 0; i < 1000; i++)
	{
		exists[i] = false;
	}
	for (int i = 0; i < 1000; i++)
	{
		value[i] = 0;
	}
	int h[1000];
	for (int i = 0; i < 1000; i++)
	{
		h[i] = 0;
	}
	int limit = 16; //15 and lower does not appear to work, not sure
					//If this is a flaw in my program or not.

	//Perfect Hashing Function for the 36 reserved words of Pascal
	for (value['E'] = 0; value['E'] < limit; value['E']++)
	{
		h[0] = myHash("ELSE");
		if (!exists[h[0]])
		{
			exists[h[0]] = true;
		}
		else
		{
			continue;
		}
		//LOOP #2 Hashed up to 1, Adding END
		//Added E
		for (value['D'] = 0; value['D'] < limit; value['D']++)
		{
			h[1] = myHash("END");
			if (!exists[h[1]])
			{
				exists[h[1]] = true;
			}
			else
			{
				continue;
			}
			//LOOP #3 Hashed up to 2, Adding Otherwise, Do, and Downto
			//Added E, D
			for (value['O'] = 0; value['O'] < limit; value['O']++)
			{
				h[2] = myHash("OTHERWISE");
				if (!exists[h[2]])
				{
					exists[h[2]] = true;
					h[3] = myHash("DO");
					if (!exists[h[3]])
					{
						exists[h[3]] = true;
						h[4] = myHash("DOWNTO");
						if (!exists[h[4]])
						{
							exists[h[4]] = true;

						}
						else
						{
							exists[h[3]] = false;
							exists[h[2]] = false;
							continue;
						}

					}
					else
					{
						exists[h[2]] = false;
						continue;
					}

				}
				else
				{
					continue;
				}
				//LOOP #4 Hashed up to 5, Adding Type, To
				//Added E, D, O
				for (value['T'] = 0; value['T'] < limit; value['T']++)
				{
					h[5] = myHash("TYPE");
					if (!exists[h[5]])
					{
						exists[h[5]] = true;
						h[6] = myHash("TO");
						if (!exists[h[6]])
						{
							exists[h[6]] = true;
						}
						else
						{
							exists[h[5]] = false;
							continue;
						}
					}
					else
					{
						continue;
					}
					//LOOP #5 Hashed up to 7, Adding File, Of
					//Added E, D, O, T
					for (value['F'] = 0; value['F'] < limit; value['F']++)
					{
						h[7] = myHash("FILE");
						if (!exists[h[7]])
						{
							exists[h[7]] = true;
							h[8] = myHash("OF");
							if (!exists[h[8]])
							{
								exists[h[8]] = true;
							}
							else
							{
								exists[h[7]] = false;
								continue;
							}
						}
						else
						{
							continue;
						}
						//Loop # 6 Hashed up to 9, Adding Not, Then, Function
						//Added E, D, O, T, F
						for (value['N'] = 0; value['N'] < limit; value['N']++)
						{
							h[9] = myHash("NOT");
							if (!exists[h[9]])
							{
								exists[h[9]] = true;
								h[10] = myHash("THEN");
								if (!exists[h[10]])
								{
									exists[h[10]] = true;
									h[11] = myHash("FUNCTION");
									if (!exists[h[11]])
									{
										exists[h[11]] = true;
									}
									else
									{
										exists[h[10]] = false;
										exists[h[9]] = false;
										continue;
									}
								}
								else
								{
									exists[h[9]] = false;
									continue;
								}
							}
							else
							{
								continue;
							}
							//LOOP #7 Hashed up to 12, Adding Record, Or, Repeat, For
							//Added E, D, O, T, F, N
							for (value['R'] = 0; value['R'] < limit; value['R']++)
							{
								h[12] = myHash("RECORD");
								if (!exists[h[12]])
								{
									exists[h[12]] = true;
									h[13] = myHash("OR");
									if (!exists[h[13]])
									{
										exists[h[13]] = true;
										h[14] = myHash("REPEAT");
										if (!exists[h[14]])
										{
											exists[h[14]] = true;
											h[15] = myHash("FOR");
											if (!exists[h[15]])
											{
												exists[h[15]] = true;
											}
											else
											{
												exists[h[14]] = false;
												exists[h[13]] = false;
												exists[h[12]] = false;
												continue;
											}
										}
										else
										{
											exists[h[13]] = false;
											exists[h[12]] = false;
											continue;
										}
									}
									else
									{
										exists[h[12]] = false;
										continue;
									}
								}
								else
								{
									continue;
								}
								//LOOP #8 Hashed up to 16, Adding Procedure, Packed
								//Added E, D, O, T, F, N, R
								for (value['P'] = 0; value['P'] < limit; value['P']++)
								{
									h[16] = myHash("PROCEDURE");
									if (!exists[h[16]])
									{
										exists[h[16]] = true;
										h[17] = myHash("PACKED");
										if (!exists[h[17]])
										{
											exists[h[17]] = true;
										}
										else
										{
											exists[h[16]] = false;
											continue;
										}
									}
									else
									{
										continue;
									}
									//LOOP #9 Hashed up to 18, Adding Case, Const
									//Added E, D, O, T, F, N, R, P
									for (value['C'] = 0; value['C'] < limit; value['C']++)
									{
										h[18] = myHash("CASE");
										if (!exists[h[18]])
										{
											exists[h[18]] = true;
											h[19] = myHash("CONST");
											if (!exists[h[19]])
											{
												exists[h[19]] = true;
											}
											else
											{
												exists[h[18]] = false;
												continue;
											}
										}
										else
										{
											continue;
										}
										//LOOP #10 Hashed up to 20, Adding While 
										//Added E, D, O, T, F, N, R, P, C
										for (value['W'] = 0; value['W'] < limit; value['W']++)
										{
											h[20] = myHash("WHILE");
											if (!exists[h[20]])
											{
												exists[h[20]] = true;
											}
											else
											{
												continue;
											}
											//LOOP #11 Hashed up to 21, Adding Div, Var
											//Added E, D, O, T, F, N, R, P, C, W
											for (value['V'] = 0; value['V'] < limit; value['V']++)
											{
												h[21] = myHash("DIV");
												if (!exists[h[21]])
												{
													exists[h[21]] = true;
													h[22] = myHash("VAR");
													if (!exists[h[22]])
													{
														exists[h[22]] = true;
													}
													else
													{
														exists[h[21]] = false;
														continue;
													}
												}
												else
												{
													continue;
												}
												//LOOP #12 Hashed up to 23, Adding And 
												//Added E, D, O, T, F, N, R, P, C, W, V
												for (value['A'] = 0; value['A'] < limit; value['A']++)
												{
													h[23] = myHash("AND");
													if (!exists[h[23]])
													{
														exists[h[23]] = true;
													}
													else
													{
														continue;
													}
													//LOOP #13 Hashed up to 24, Adding Mod, Program
													//Added E, D, O, T, F, N, R, P, C, W, V, A
													for (value['M'] = 0; value['M'] < limit; value['M']++)
													{
														h[24] = myHash("MOD");
														if (!exists[h[24]])
														{
															exists[h[24]] = true;
															h[25] = myHash("PROGRAM");
															if (!exists[h[25]])
															{
																exists[h[25]] = true;
															}
															else
															{
																exists[h[24]] = false;
																continue;
															}
														}
														else
														{
															continue;
														}
														//LOOP #14 Hashed up to 26, Adding Nil, Label
														//Added E, D, O, T, F, N, R, P, C, W, V, A, M
														for (value['L'] = 0; value['L'] < limit; value['L']++)
														{
															h[26] = myHash("NIL");
															if (!exists[h[26]])
															{
																exists[h[26]] = true;
																h[27] = myHash("LABEL");
																if (!exists[h[27]])
																{
																	exists[h[27]] = true;
																}
																else
																{
																	exists[h[26]] = false;
																	continue;
																}
															}
															else
															{
																continue;
															}
															//LOOP #15 Hashed up to 28, Adding In, If
															//Added E, D, O, T, F, N, R, P, C, W, V, A, M, L
															for (value['I'] = 0; value['I'] < limit; value['I']++)
															{
																h[28] = myHash("IN");
																if (!exists[h[28]])
																{
																	exists[h[28]] = true;
																	h[29] = myHash("IF");
																	if (!exists[h[29]])
																	{
																		exists[h[29]] = true;
																	}
																	else
																	{
																		exists[h[28]] = false;
																		continue;
																	}
																}
																else
																{
																	continue;
																}
																//LOOP #16 Hashed up to 30, Adding Goto
																//Added E, D, O, T, F, N, R, P, C, W, V, A, M, L, I
																for (value['G'] = 0; value['G'] < limit; value['G']++)
																{
																	h[30] = myHash("GOTO");
																	if (!exists[h[30]])
																	{
																		exists[h[30]] = true;
																	}
																	else
																	{
																		continue;
																	}
																	//LOOP #17 Hashed up to 31, Adding SET
																	//Added E, D, O, T, F, N, R, P, C, W, V, A, M, L, I, G
																	for (value['S'] = 0; value['S'] < limit; value['S']++)
																	{
																		h[31] = myHash("SET");
																		if (!exists[h[31]])
																		{
																			exists[h[31]] = true;
																		}
																		else
																		{
																			continue;
																		}
																		//LOOP #18 Hashed up to 32, Adding Begin
																		//Added E, D, O, T, F, N, R, P, C, W, V, A, M, L, I, G, S
																		for (value['B'] = 0; value['B'] < limit; value['B']++)
																		{
																			h[32] = myHash("BEGIN");
																			if (!exists[h[32]])
																			{
																				exists[h[32]] = true;
																			}
																			else
																			{
																				continue;
																			}
																			//LOOP #19 Hashed up to 33, Adding UNTIL 
																			//Added E, D, O, T, F, N, R, P, C, W, V, A, M, L, I, G, S, B
																			for (value['U'] = 0; value['U'] < limit; value['U']++)
																			{
																				h[33] = myHash("UNTIL");
																				if (!exists[h[33]])
																				{
																					exists[h[33]] = true;
																				}
																				else
																				{
																					continue;
																				}
																				//LOOP #20 Hashed up to 34, Adding ARRAY 
																				//Added E, D, O, T, F, N, R, P, C, W, V, A, M, L, I, G, S, B, U
																				for (value['Y'] = 0; value['Y'] < limit; value['Y']++)
																				{
																					h[34] = myHash("ARRAY");
																					if (!exists[h[34]])
																					{
																						exists[h[34]] = true;
																					}
																					else
																					{
																						continue;
																					}
																					//LOOP #21 Hashed up to 35, Adding WITH
																					//Added E, D, O, T, F, N, R, P, C, W, V, A, M, L, I, G, S, B, U, Y
																					for (value['H'] = 0; value['H'] < limit; value['H']++)
																					{
																						h[35] = myHash("WITH");
																						if (!exists[h[35]])
																						{
																							for (char i = 'A'; i <= 'Z'; i++)
																							{
																								cout << i << " = " << value[i] << endl;
																							}
																							cout << endl;
																							for (int i = 0; i <= 35; i++)
																							{
																								cout << "h[" << i << "] = " << h[i] << endl;
																							}
																							//Function is done! Halt here and exit
																							system("PAUSE");
																							exit(0);
																						}
																					}
																					//Closing  Loop H
																					exists[h[34]] = false;
																					//cout << "Closing H Loop \n";
																				}
																				//Closing  Loop Y
																				exists[h[33]] = false;
																				//cout << "Closing Y Loop \n";
																			}
																			//Closing  Loop U
																			exists[h[32]] = false;
																			//cout << "Closing U Loop \n";
																		}
																		//Closing  Loop B
																		exists[h[31]] = false;
																		//cout << "Closing B Loop \n";
																	}
																	//Closing  Loop S
																	exists[h[30]] = false;
																	//cout << "Closing S Loop \n";
																}
																//Closing  Loop G
																exists[h[28]] = exists[h[29]] = false;
																//cout << "Closing G Loop \n";
															}
															//Closing  Loop I
															exists[h[26]] = exists[h[27]] = false;
															//cout << "Closing I Loop \n";
														}
														//Closing  Loop L
														exists[h[24]] = exists[h[25]] = false;
														//cout << "Closing L Loop \n";
													}
													//Closing  Loop M
													exists[h[23]] = false;
													//cout << "Closing M Loop \n";
												}
												//Closing  Loop A
												exists[h[21]] = exists[h[22]] = false;
												//cout << "Closing A Loop \n";
											}
											//Closing  Loop V
											exists[h[20]] = false;
											//cout << "Closing V Loop \n";
										}
										//Closing  Loop W
										exists[h[18]] = exists[h[19]] = false;
										//cout << "Closing W Loop \n";
									}
									//Closing  Loop C
									exists[h[16]] = exists[h[17]] = false;
									//cout << "Closing C Loop \n";
								}
								//Closing  Loop P
								exists[h[12]] = exists[h[13]] = exists[h[14]] = exists[h[15]] = false;
								//cout << "Closing P Loop \n";
							}
							//Closing  Loop R
							exists[h[9]] = exists[h[10]] = exists[h[11]] = false;
							//cout << "Closing R Loop \n";
						}
						//Closing  Loop N
						exists[h[7]] = exists[h[8]] = false;
						//cout << "Closing N Loop \n";
					}
					//Closing F loop
					exists[h[5]] = exists[h[6]] = false;
					//cout << "Closing F Loop \n";
				}
				//Closing T loop
				exists[h[2]] = exists[h[3]] = exists[h[4]] = false;
				//cout << "Closing T Loop \n";
			}
			//Closing O loop
			exists[h[1]] = false;
			//cout << "Closing O Loop \n";
		}
		//Closing D loop
		exists[h[0]] = false;
		//cout << "Closing D Loop \n";
	}
	//Closing E loop
	//cout << "Closing E Loop \n";
	cout << "No values were found. \n";
	system("PAUSE");
	return EXIT_SUCCESS;
}