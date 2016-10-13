

#include "TotemT1LG.hpp"

#include <TMath.h>


double GetY_TotemT1LG(int channel)
{
  const static double mapy[384]=
    {

/*	0	*/	0	,
/*	1	*/	0	,
/*	2	*/	0	,
/*	3	*/	39.84	,
/*	4	*/	41.93	,
/*	5	*/	44.13	,
/*	6	*/	46.44	,
/*	7	*/	48.87	,
/*	8	*/	51.42	,
/*	9	*/	54.12	,
/*	10	*/	56.95	,
/*	11	*/	59.93	,
/*	12	*/	62.62	,
/*	13	*/	65.92	,
/*	14	*/	69.85	,
/*	15	*/	73.5	,
/*	16	*/	77.35	,
/*	17	*/	81.4	,
/*	18	*/	85.66	,
/*	19	*/	89.71	,
/*	20	*/	94.43	,
/*	21	*/	99.83	,
/*	22	*/	105.05	,
/*	23	*/	110.55	,
/*	24	*/	116.34	,
/*	25	*/	122.43	,
/*	26	*/	128.84	,
/*	27	*/	38.86	,
/*	28	*/	40.9	,
/*	29	*/	43.04	,
/*	30	*/	45.29	,
/*	31	*/	47.66	,
/*	32	*/	50.16	,
/*	33	*/	52.78	,
/*	34	*/	55.55	,
/*	35	*/	58.45	,
/*	36	*/	61.07	,
/*	37	*/	64.29	,
/*	38	*/	68.12	,
/*	39	*/	71.69	,
/*	40	*/	75.44	,
/*	41	*/	79.39	,
/*	42	*/	83.55	,
/*	43	*/	87.49	,
/*	44	*/	92.1	,
/*	45	*/	97.37	,
/*	46	*/	102.46	,
/*	47	*/	107.82	,
/*	48	*/	113.47	,
/*	49	*/	119.41	,
/*	50	*/	125.66	,
/*	51	*/	37.77	,
/*	52	*/	39.75	,
/*	53	*/	41.83	,
/*	54	*/	44.02	,
/*	55	*/	46.32	,
/*	56	*/	48.75	,
/*	57	*/	51.3	,
/*	58	*/	53.99	,
/*	59	*/	56.81	,
/*	60	*/	59.36	,
/*	61	*/	62.49	,
/*	62	*/	66.21	,
/*	63	*/	69.68	,
/*	64	*/	73.33	,
/*	65	*/	77.17	,
/*	66	*/	81.21	,
/*	67	*/	85.04	,
/*	68	*/	89.51	,
/*	69	*/	94.64	,
/*	70	*/	99.59	,
/*	71	*/	104.8	,
/*	72	*/	110.29	,
/*	73	*/	116.06	,
/*	74	*/	122.14	,
/*	75	*/	36.58	,
/*	76	*/	38.49	,
/*	77	*/	40.51	,
/*	78	*/	42.63	,
/*	79	*/	44.86	,
/*	80	*/	47.21	,
/*	81	*/	49.68	,
/*	82	*/	52.28	,
/*	83	*/	55.02	,
/*	84	*/	57.49	,
/*	85	*/	60.52	,
/*	86	*/	64.12	,
/*	87	*/	67.48	,
/*	88	*/	71.01	,
/*	89	*/	74.73	,
/*	90	*/	78.64	,
/*	91	*/	82.35	,
/*	92	*/	86.69	,
/*	93	*/	91.65	,
/*	94	*/	96.44	,
/*	95	*/	101.49	,
/*	96	*/	106.8	,
/*	97	*/	112.4	,
/*	98	*/	118.28	,
/*	99	*/	35.28	,
/*	100	*/	37.13	,
/*	101	*/	39.08	,
/*	102	*/	41.12	,
/*	103	*/	43.28	,
/*	104	*/	45.54	,
/*	105	*/	47.92	,
/*	106	*/	50.43	,
/*	107	*/	53.07	,
/*	108	*/	55.45	,
/*	109	*/	58.38	,
/*	110	*/	61.85	,
/*	111	*/	65.09	,
/*	112	*/	68.5	,
/*	113	*/	72.09	,
/*	114	*/	75.86	,
/*	115	*/	79.44	,
/*	116	*/	83.62	,
/*	117	*/	88.41	,
/*	118	*/	93.03	,
/*	119	*/	97.9	,
/*	120	*/	103.03	,
/*	121	*/	108.42	,
/*	122	*/	114.1	,
/*	123	*/	0	,
/*	124	*/	0	,
/*	125	*/	0	,
/*	126	*/	0	,
/*	127	*/	0	,
/*	128	*/	0	,
/*	129	*/	0	,
/*	130	*/	0	,
/*	131	*/	33.89	,
/*	132	*/	35.67	,
/*	133	*/	37.54	,
/*	134	*/	39.5	,
/*	135	*/	41.57	,
/*	136	*/	43.75	,
/*	137	*/	46.04	,
/*	138	*/	48.45	,
/*	139	*/	50.98	,
/*	140	*/	53.27	,
/*	141	*/	56.08	,
/*	142	*/	59.42	,
/*	143	*/	62.53	,
/*	144	*/	65.8	,
/*	145	*/	69.25	,
/*	146	*/	72.87	,
/*	147	*/	76.31	,
/*	148	*/	80.33	,
/*	149	*/	84.92	,
/*	150	*/	89.37	,
/*	151	*/	94.05	,
/*	152	*/	98.97	,
/*	153	*/	104.15	,
/*	154	*/	109.6	,
/*	155	*/	32.41	,
/*	156	*/	34.11	,
/*	157	*/	35.89	,
/*	158	*/	37.77	,
/*	159	*/	39.75	,
/*	160	*/	41.83	,
/*	161	*/	44.02	,
/*	162	*/	46.33	,
/*	163	*/	48.75	,
/*	164	*/	50.94	,
/*	165	*/	53.62	,
/*	166	*/	56.82	,
/*	167	*/	59.79	,
/*	168	*/	62.92	,
/*	169	*/	66.22	,
/*	170	*/	69.68	,
/*	171	*/	72.97	,
/*	172	*/	76.81	,
/*	173	*/	81.21	,
/*	174	*/	85.46	,
/*	175	*/	89.93	,
/*	176	*/	94.64	,
/*	177	*/	99.59	,
/*	178	*/	104.81	,
/*	179	*/	30.84	,
/*	180	*/	32.45	,
/*	181	*/	34.15	,
/*	182	*/	35.94	,
/*	183	*/	37.82	,
/*	184	*/	39.8	,
/*	185	*/	41.89	,
/*	186	*/	44.08	,
/*	187	*/	46.39	,
/*	188	*/	48.47	,
/*	189	*/	51.02	,
/*	190	*/	54.06	,
/*	191	*/	56.89	,
/*	192	*/	59.87	,
/*	193	*/	63.01	,
/*	194	*/	66.3	,
/*	195	*/	69.43	,
/*	196	*/	73.09	,
/*	197	*/	77.27	,
/*	198	*/	81.31	,
/*	199	*/	85.57	,
/*	200	*/	90.05	,
/*	201	*/	94.76	,
/*	202	*/	99.72	,
/*	203	*/	29.18	,
/*	204	*/	30.71	,
/*	205	*/	32.32	,
/*	206	*/	34.01	,
/*	207	*/	35.79	,
/*	208	*/	37.67	,
/*	209	*/	39.64	,
/*	210	*/	41.71	,
/*	211	*/	43.9	,
/*	212	*/	45.87	,
/*	213	*/	48.28	,
/*	214	*/	51.16	,
/*	215	*/	53.84	,
/*	216	*/	56.66	,
/*	217	*/	59.62	,
/*	218	*/	62.74	,
/*	219	*/	65.71	,
/*	220	*/	69.16	,
/*	221	*/	73.12	,
/*	222	*/	76.95	,
/*	223	*/	80.97	,
/*	224	*/	85.21	,
/*	225	*/	89.67	,
/*	226	*/	94.37	,
/*	227	*/	27.45	,
/*	228	*/	28.88	,
/*	229	*/	30.4	,
/*	230	*/	31.99	,
/*	231	*/	33.66	,
/*	232	*/	35.43	,
/*	233	*/	37.28	,
/*	234	*/	39.23	,
/*	235	*/	41.29	,
/*	236	*/	43.14	,
/*	237	*/	45.41	,
/*	238	*/	48.12	,
/*	239	*/	50.63	,
/*	240	*/	53.29	,
/*	241	*/	56.07	,
/*	242	*/	59.01	,
/*	243	*/	61.8	,
/*	244	*/	65.05	,
/*	245	*/	68.77	,
/*	246	*/	72.37	,
/*	247	*/	76.16	,
/*	248	*/	80.14	,
/*	249	*/	84.34	,
/*	250	*/	88.75	,
/*	251	*/	0	,
/*	252	*/	0	,
/*	253	*/	0	,
/*	254	*/	0	,
/*	255	*/	0	,
/*	256	*/	0	,
/*	257	*/	0	,
/*	258	*/	0	,
/*	259	*/	25.64	,
/*	260	*/	26.98	,
/*	261	*/	28.39	,
/*	262	*/	29.88	,
/*	263	*/	31.44	,
/*	264	*/	33.09	,
/*	265	*/	34.82	,
/*	266	*/	36.64	,
/*	267	*/	38.56	,
/*	268	*/	40.29	,
/*	269	*/	42.41	,
/*	270	*/	44.94	,
/*	271	*/	47.29	,
/*	272	*/	49.77	,
/*	273	*/	52.37	,
/*	274	*/	55.12	,
/*	275	*/	57.72	,
/*	276	*/	60.75	,
/*	277	*/	64.23	,
/*	278	*/	67.59	,
/*	279	*/	71.13	,
/*	280	*/	74.85	,
/*	281	*/	78.77	,
/*	282	*/	82.9	,
/*	283	*/	23.75	,
/*	284	*/	25	,
/*	285	*/	26.31	,
/*	286	*/	27.68	,
/*	287	*/	29.13	,
/*	288	*/	30.66	,
/*	289	*/	32.26	,
/*	290	*/	33.95	,
/*	291	*/	35.73	,
/*	292	*/	37.33	,
/*	293	*/	39.3	,
/*	294	*/	41.64	,
/*	295	*/	43.82	,
/*	296	*/	46.12	,
/*	297	*/	48.53	,
/*	298	*/	51.07	,
/*	299	*/	53.48	,
/*	300	*/	56.29	,
/*	301	*/	59.52	,
/*	302	*/	62.63	,
/*	303	*/	65.91	,
/*	304	*/	69.36	,
/*	305	*/	72.99	,
/*	306	*/	76.81	,
/*	307	*/	21.81	,
/*	308	*/	22.95	,
/*	309	*/	24.15	,
/*	310	*/	25.41	,
/*	311	*/	26.75	,
/*	312	*/	28.15	,
/*	313	*/	29.62	,
/*	314	*/	31.17	,
/*	315	*/	32.8	,
/*	316	*/	34.27	,
/*	317	*/	36.08	,
/*	318	*/	38.23	,
/*	319	*/	40.23	,
/*	320	*/	42.34	,
/*	321	*/	44.55	,
/*	322	*/	46.88	,
/*	323	*/	49.1	,
/*	324	*/	51.68	,
/*	325	*/	54.64	,
/*	326	*/	57.5	,
/*	327	*/	60.51	,
/*	328	*/	63.67	,
/*	329	*/	67.01	,
/*	330	*/	70.52	,
/*	331	*/	19.8	,
/*	332	*/	20.84	,
/*	333	*/	21.93	,
/*	334	*/	23.08	,
/*	335	*/	24.28	,
/*	336	*/	25.56	,
/*	337	*/	26.89	,
/*	338	*/	28.3	,
/*	339	*/	29.78	,
/*	340	*/	31.12	,
/*	341	*/	32.76	,
/*	342	*/	34.71	,
/*	343	*/	36.53	,
/*	344	*/	38.44	,
/*	345	*/	40.45	,
/*	346	*/	42.57	,
/*	347	*/	44.58	,
/*	348	*/	46.93	,
/*	349	*/	49.61	,
/*	350	*/	52.21	,
/*	351	*/	54.94	,
/*	352	*/	57.82	,
/*	353	*/	60.84	,
/*	354	*/	64.03	,
/*	355	*/	17.74	,
/*	356	*/	18.67	,
/*	357	*/	19.65	,
/*	358	*/	20.67	,
/*	359	*/	21.76	,
/*	360	*/	22.9	,
/*	361	*/	24.09	,
/*	362	*/	25.36	,
/*	363	*/	26.68	,
/*	364	*/	27.88	,
/*	365	*/	29.35	,
/*	366	*/	31.1	,
/*	367	*/	32.73	,
/*	368	*/	34.44	,
/*	369	*/	36.24	,
/*	370	*/	38.14	,
/*	371	*/	39.94	,
/*	372	*/	42.04	,
/*	373	*/	44.45	,
/*	374	*/	46.77	,
/*	375	*/	49.22	,
/*	376	*/	51.8	,
/*	377	*/	54.51	,
/*	378	*/	57.36	,
/*	379	*/	0	,
/*	380	*/	0	,
/*	381	*/	0	,
/*	382	*/	0	,
/*	383	*/	0	


    };

	 
  return mapy[channel];
}

double GetX_TotemT1LG(int channel)
{
  const static double mapx[384] =
    {

/*	0	*/	0	,
/*	1	*/	0	,
/*	2	*/	0	,
/*	3	*/	-17.74	,
/*	4	*/	-18.67	,
/*	5	*/	-19.65	,
/*	6	*/	-20.67	,
/*	7	*/	-21.76	,
/*	8	*/	-22.9	,
/*	9	*/	-24.09	,
/*	10	*/	-25.36	,
/*	11	*/	-26.68	,
/*	12	*/	-27.88	,
/*	13	*/	-29.35	,
/*	14	*/	-31.1	,
/*	15	*/	-32.73	,
/*	16	*/	-34.44	,
/*	17	*/	-36.24	,
/*	18	*/	-38.14	,
/*	19	*/	-39.94	,
/*	20	*/	-42.04	,
/*	21	*/	-44.45	,
/*	22	*/	-46.77	,
/*	23	*/	-49.22	,
/*	24	*/	-51.8	,
/*	25	*/	-54.51	,
/*	26	*/	-57.36	,
/*	27	*/	-19.8	,
/*	28	*/	-20.84	,
/*	29	*/	-21.93	,
/*	30	*/	-23.08	,
/*	31	*/	-24.28	,
/*	32	*/	-25.56	,
/*	33	*/	-26.89	,
/*	34	*/	-28.3	,
/*	35	*/	-29.78	,
/*	36	*/	-31.12	,
/*	37	*/	-32.76	,
/*	38	*/	-34.71	,
/*	39	*/	-36.53	,
/*	40	*/	-38.44	,
/*	41	*/	-40.45	,
/*	42	*/	-42.57	,
/*	43	*/	-44.58	,
/*	44	*/	-46.93	,
/*	45	*/	-49.61	,
/*	46	*/	-52.21	,
/*	47	*/	-54.94	,
/*	48	*/	-57.82	,
/*	49	*/	-60.84	,
/*	50	*/	-64.03	,
/*	51	*/	-21.81	,
/*	52	*/	-22.95	,
/*	53	*/	-24.15	,
/*	54	*/	-25.41	,
/*	55	*/	-26.75	,
/*	56	*/	-28.15	,
/*	57	*/	-29.62	,
/*	58	*/	-31.17	,
/*	59	*/	-32.8	,
/*	60	*/	-34.27	,
/*	61	*/	-36.08	,
/*	62	*/	-38.23	,
/*	63	*/	-40.23	,
/*	64	*/	-42.34	,
/*	65	*/	-44.55	,
/*	66	*/	-46.88	,
/*	67	*/	-49.1	,
/*	68	*/	-51.68	,
/*	69	*/	-54.64	,
/*	70	*/	-57.5	,
/*	71	*/	-60.51	,
/*	72	*/	-63.67	,
/*	73	*/	-67.01	,
/*	74	*/	-70.52	,
/*	75	*/	-23.75	,
/*	76	*/	-25	,
/*	77	*/	-26.31	,
/*	78	*/	-27.68	,
/*	79	*/	-29.13	,
/*	80	*/	-30.66	,
/*	81	*/	-32.26	,
/*	82	*/	-33.95	,
/*	83	*/	-35.73	,
/*	84	*/	-37.33	,
/*	85	*/	-39.3	,
/*	86	*/	-41.64	,
/*	87	*/	-43.82	,
/*	88	*/	-46.12	,
/*	89	*/	-48.53	,
/*	90	*/	-51.07	,
/*	91	*/	-53.48	,
/*	92	*/	-56.29	,
/*	93	*/	-59.52	,
/*	94	*/	-62.63	,
/*	95	*/	-65.91	,
/*	96	*/	-69.36	,
/*	97	*/	-72.99	,
/*	98	*/	-76.81	,
/*	99	*/	-25.64	,
/*	100	*/	-26.98	,
/*	101	*/	-28.39	,
/*	102	*/	-29.88	,
/*	103	*/	-31.44	,
/*	104	*/	-33.09	,
/*	105	*/	-34.82	,
/*	106	*/	-36.64	,
/*	107	*/	-38.56	,
/*	108	*/	-40.29	,
/*	109	*/	-42.41	,
/*	110	*/	-44.94	,
/*	111	*/	-47.29	,
/*	112	*/	-49.77	,
/*	113	*/	-52.37	,
/*	114	*/	-55.12	,
/*	115	*/	-57.72	,
/*	116	*/	-60.75	,
/*	117	*/	-64.23	,
/*	118	*/	-67.59	,
/*	119	*/	-71.13	,
/*	120	*/	-74.85	,
/*	121	*/	-78.77	,
/*	122	*/	-82.9	,
/*	123	*/	0	,
/*	124	*/	0	,
/*	125	*/	0	,
/*	126	*/	0	,
/*	127	*/	0	,
/*	128	*/	0	,
/*	129	*/	0	,
/*	130	*/	0	,
/*	131	*/	-27.45	,
/*	132	*/	-28.88	,
/*	133	*/	-30.4	,
/*	134	*/	-31.99	,
/*	135	*/	-33.66	,
/*	136	*/	-35.43	,
/*	137	*/	-37.28	,
/*	138	*/	-39.23	,
/*	139	*/	-41.29	,
/*	140	*/	-43.14	,
/*	141	*/	-45.41	,
/*	142	*/	-48.12	,
/*	143	*/	-50.63	,
/*	144	*/	-53.29	,
/*	145	*/	-56.07	,
/*	146	*/	-59.01	,
/*	147	*/	-61.8	,
/*	148	*/	-65.05	,
/*	149	*/	-68.77	,
/*	150	*/	-72.37	,
/*	151	*/	-76.16	,
/*	152	*/	-80.14	,
/*	153	*/	-84.34	,
/*	154	*/	-88.75	,
/*	155	*/	-29.18	,
/*	156	*/	-30.71	,
/*	157	*/	-32.32	,
/*	158	*/	-34.01	,
/*	159	*/	-35.79	,
/*	160	*/	-37.67	,
/*	161	*/	-39.64	,
/*	162	*/	-41.71	,
/*	163	*/	-43.9	,
/*	164	*/	-45.87	,
/*	165	*/	-48.28	,
/*	166	*/	-51.16	,
/*	167	*/	-53.84	,
/*	168	*/	-56.66	,
/*	169	*/	-59.62	,
/*	170	*/	-62.74	,
/*	171	*/	-65.71	,
/*	172	*/	-69.16	,
/*	173	*/	-73.12	,
/*	174	*/	-76.95	,
/*	175	*/	-80.97	,
/*	176	*/	-85.21	,
/*	177	*/	-89.67	,
/*	178	*/	-94.37	,
/*	179	*/	-30.84	,
/*	180	*/	-32.45	,
/*	181	*/	-34.15	,
/*	182	*/	-35.94	,
/*	183	*/	-37.82	,
/*	184	*/	-39.8	,
/*	185	*/	-41.89	,
/*	186	*/	-44.08	,
/*	187	*/	-46.39	,
/*	188	*/	-48.47	,
/*	189	*/	-51.02	,
/*	190	*/	-54.06	,
/*	191	*/	-56.89	,
/*	192	*/	-59.87	,
/*	193	*/	-63.01	,
/*	194	*/	-66.3	,
/*	195	*/	-69.43	,
/*	196	*/	-73.09	,
/*	197	*/	-77.27	,
/*	198	*/	-81.31	,
/*	199	*/	-85.57	,
/*	200	*/	-90.05	,
/*	201	*/	-94.76	,
/*	202	*/	-99.72	,
/*	203	*/	-32.41	,
/*	204	*/	-34.11	,
/*	205	*/	-35.89	,
/*	206	*/	-37.77	,
/*	207	*/	-39.75	,
/*	208	*/	-41.83	,
/*	209	*/	-44.02	,
/*	210	*/	-46.33	,
/*	211	*/	-48.75	,
/*	212	*/	-50.94	,
/*	213	*/	-53.62	,
/*	214	*/	-56.82	,
/*	215	*/	-59.79	,
/*	216	*/	-62.92	,
/*	217	*/	-66.22	,
/*	218	*/	-69.68	,
/*	219	*/	-72.97	,
/*	220	*/	-76.81	,
/*	221	*/	-81.21	,
/*	222	*/	-85.46	,
/*	223	*/	-89.93	,
/*	224	*/	-94.64	,
/*	225	*/	-99.59	,
/*	226	*/	-104.81	,
/*	227	*/	-33.89	,
/*	228	*/	-35.67	,
/*	229	*/	-37.54	,
/*	230	*/	-39.5	,
/*	231	*/	-41.57	,
/*	232	*/	-43.75	,
/*	233	*/	-46.04	,
/*	234	*/	-48.45	,
/*	235	*/	-50.98	,
/*	236	*/	-53.27	,
/*	237	*/	-56.08	,
/*	238	*/	-59.42	,
/*	239	*/	-62.53	,
/*	240	*/	-65.8	,
/*	241	*/	-69.25	,
/*	242	*/	-72.87	,
/*	243	*/	-76.31	,
/*	244	*/	-80.33	,
/*	245	*/	-84.92	,
/*	246	*/	-89.37	,
/*	247	*/	-94.05	,
/*	248	*/	-98.97	,
/*	249	*/	-104.15	,
/*	250	*/	-109.6	,
/*	251	*/	0	,
/*	252	*/	0	,
/*	253	*/	0	,
/*	254	*/	0	,
/*	255	*/	0	,
/*	256	*/	0	,
/*	257	*/	0	,
/*	258	*/	0	,
/*	259	*/	-35.28	,
/*	260	*/	-37.13	,
/*	261	*/	-39.08	,
/*	262	*/	-41.12	,
/*	263	*/	-43.28	,
/*	264	*/	-45.54	,
/*	265	*/	-47.92	,
/*	266	*/	-50.43	,
/*	267	*/	-53.07	,
/*	268	*/	-55.45	,
/*	269	*/	-58.38	,
/*	270	*/	-61.85	,
/*	271	*/	-65.09	,
/*	272	*/	-68.5	,
/*	273	*/	-72.09	,
/*	274	*/	-75.86	,
/*	275	*/	-79.44	,
/*	276	*/	-83.62	,
/*	277	*/	-88.41	,
/*	278	*/	-93.03	,
/*	279	*/	-97.9	,
/*	280	*/	-103.03	,
/*	281	*/	-108.42	,
/*	282	*/	-114.1	,
/*	283	*/	-36.58	,
/*	284	*/	-38.49	,
/*	285	*/	-40.51	,
/*	286	*/	-42.63	,
/*	287	*/	-44.86	,
/*	288	*/	-47.21	,
/*	289	*/	-49.68	,
/*	290	*/	-52.28	,
/*	291	*/	-55.02	,
/*	292	*/	-57.49	,
/*	293	*/	-60.52	,
/*	294	*/	-64.12	,
/*	295	*/	-67.48	,
/*	296	*/	-71.01	,
/*	297	*/	-74.73	,
/*	298	*/	-78.64	,
/*	299	*/	-82.35	,
/*	300	*/	-86.69	,
/*	301	*/	-91.65	,
/*	302	*/	-96.44	,
/*	303	*/	-101.49	,
/*	304	*/	-106.8	,
/*	305	*/	-112.4	,
/*	306	*/	-118.28	,
/*	307	*/	-37.77	,
/*	308	*/	-39.75	,
/*	309	*/	-41.83	,
/*	310	*/	-44.02	,
/*	311	*/	-46.32	,
/*	312	*/	-48.75	,
/*	313	*/	-51.3	,
/*	314	*/	-53.99	,
/*	315	*/	-56.81	,
/*	316	*/	-59.36	,
/*	317	*/	-62.49	,
/*	318	*/	-66.21	,
/*	319	*/	-69.68	,
/*	320	*/	-73.33	,
/*	321	*/	-77.17	,
/*	322	*/	-81.21	,
/*	323	*/	-85.04	,
/*	324	*/	-89.51	,
/*	325	*/	-94.64	,
/*	326	*/	-99.59	,
/*	327	*/	-104.8	,
/*	328	*/	-110.29	,
/*	329	*/	-116.06	,
/*	330	*/	-122.14	,
/*	331	*/	-38.86	,
/*	332	*/	-40.9	,
/*	333	*/	-43.04	,
/*	334	*/	-45.29	,
/*	335	*/	-47.66	,
/*	336	*/	-50.16	,
/*	337	*/	-52.78	,
/*	338	*/	-55.55	,
/*	339	*/	-58.45	,
/*	340	*/	-61.07	,
/*	341	*/	-64.29	,
/*	342	*/	-68.12	,
/*	343	*/	-71.69	,
/*	344	*/	-75.44	,
/*	345	*/	-79.39	,
/*	346	*/	-83.55	,
/*	347	*/	-87.49	,
/*	348	*/	-92.1	,
/*	349	*/	-97.37	,
/*	350	*/	-102.46	,
/*	351	*/	-107.82	,
/*	352	*/	-113.47	,
/*	353	*/	-119.41	,
/*	354	*/	-125.66	,
/*	355	*/	-39.84	,
/*	356	*/	-41.93	,
/*	357	*/	-44.13	,
/*	358	*/	-46.44	,
/*	359	*/	-48.87	,
/*	360	*/	-51.42	,
/*	361	*/	-54.12	,
/*	362	*/	-56.95	,
/*	363	*/	-59.93	,
/*	364	*/	-62.62	,
/*	365	*/	-65.92	,
/*	366	*/	-69.85	,
/*	367	*/	-73.5	,
/*	368	*/	-77.35	,
/*	369	*/	-81.4	,
/*	370	*/	-85.66	,
/*	371	*/	-89.71	,
/*	372	*/	-94.43	,
/*	373	*/	-99.83	,
/*	374	*/	-105.05	,
/*	375	*/	-110.55	,
/*	376	*/	-116.34	,
/*	377	*/	-122.43	,
/*	378	*/	-128.84	,
/*	379	*/	0	,
/*	380	*/	0	,
/*	381	*/	0	,
/*	382	*/	0	,
/*	383	*/	0	


    };
  

  return mapx[channel];

}

double GetR_TotemT1LG(int channel)
{
  const static double mapr[256] =
    {
/*0*/	42.5	,
/*1*/	42.9	,
/*2*/	43.3	,
/*3*/	43.7	,
/*4*/	44.1	,
/*5*/	44.5	,
/*6*/	44.9	,
/*7*/	45.3	,
/*8*/	45.7	,
/*9*/	46.1	,
/*10*/	46.5	,
/*11*/	46.9	,
/*12*/	47.3	,
/*13*/	47.7	,
/*14*/	48.1	,
/*15*/	48.5	,
/*16*/	48.9	,
/*17*/	49.3	,
/*18*/	49.7	,
/*19*/	50.1	,
/*20*/	50.5	,
/*21*/	50.9	,
/*22*/	51.3	,
/*23*/	51.7	,
/*24*/	52.1	,
/*25*/	52.5	,
/*26*/	52.9	,
/*27*/	53.3	,
/*28*/	53.7	,
/*29*/	54.1	,
/*30*/	54.5	,
/*31*/	54.9	,
/*32*/	55.3	,
/*33*/	55.7	,
/*34*/	56.1	,
/*35*/	56.5	,
/*36*/	56.9	,
/*37*/	57.3	,
/*38*/	57.7	,
/*39*/	58.1	,
/*40*/	58.5	,
/*41*/	58.9	,
/*42*/	59.3	,
/*43*/	59.7	,
/*44*/	60.1	,
/*45*/	60.5	,
/*46*/	60.9	,
/*47*/	61.3	,
/*48*/	61.7	,
/*49*/	62.1	,
/*50*/	62.5	,
/*51*/	62.9	,
/*52*/	63.3	,
/*53*/	63.7	,
/*54*/	64.1	,
/*55*/	64.5	,
/*56*/	64.9	,
/*57*/	65.3	,
/*58*/	65.7	,
/*59*/	66.1	,
/*60*/	66.5	,
/*61*/	66.9	,
/*62*/	67.3	,
/*63*/	67.7	,
/*64*/	68.1	,
/*65*/	68.5	,
/*66*/	68.9	,
/*67*/	69.3	,
/*68*/	69.7	,
/*69*/	70.1	,
/*70*/	70.5	,
/*71*/	70.9	,
/*72*/	71.3	,
/*73*/	71.7	,
/*74*/	72.1	,
/*75*/	72.5	,
/*76*/	72.9	,
/*77*/	73.3	,
/*78*/	73.7	,
/*79*/	74.1	,
/*80*/	74.5	,
/*81*/	74.9	,
/*82*/	75.3	,
/*83*/	75.7	,
/*84*/	76.1	,
/*85*/	76.5	,
/*86*/	76.9	,
/*87*/	77.3	,
/*88*/	77.7	,
/*89*/	78.1	,
/*90*/	78.5	,
/*91*/	78.9	,
/*92*/	79.3	,
/*93*/	79.7	,
/*94*/	80.1	,
/*95*/	80.5	,
/*96*/	80.9	,
/*97*/	81.3	,
/*98*/	81.7	,
/*99*/	82.1	,
/*100*/	82.5	,
/*101*/	82.9	,
/*102*/	83.3	,
/*103*/	83.7	,
/*104*/	84.1	,
/*105*/	84.5	,
/*106*/	84.9	,
/*107*/	85.3	,
/*108*/	85.7	,
/*109*/	86.1	,
/*110*/	86.5	,
/*111*/	86.9	,
/*112*/	87.3	,
/*113*/	87.7	,
/*114*/	88.1	,
/*115*/	88.5	,
/*116*/	88.9	,
/*117*/	89.3	,
/*118*/	89.7	,
/*119*/	90.1	,
/*120*/	90.5	,
/*121*/	90.9	,
/*122*/	91.3	,
/*123*/	91.7	,
/*124*/	92.1	,
/*125*/	92.5	,
/*126*/	92.9	,
/*127*/	93.3	,
/*128*/	93.7	,
/*129*/	94.1	,
/*130*/	94.5	,
/*131*/	94.9	,
/*132*/	95.3	,
/*133*/	95.7	,
/*134*/	96.1	,
/*135*/	96.5	,
/*136*/	96.9	,
/*137*/	97.3	,
/*138*/	97.7	,
/*139*/	98.1	,
/*140*/	98.5	,
/*141*/	98.9	,
/*142*/	99.3	,
/*143*/	99.7	,
/*144*/	100.1	,
/*145*/	100.5	,
/*146*/	100.9	,
/*147*/	101.3	,
/*148*/	101.7	,
/*149*/	102.1	,
/*150*/	102.5	,
/*151*/	102.9	,
/*152*/	103.3	,
/*153*/	103.7	,
/*154*/	104.1	,
/*155*/	104.5	,
/*156*/	104.9	,
/*157*/	105.3	,
/*158*/	105.7	,
/*159*/	106.1	,
/*160*/	106.5	,
/*161*/	106.9	,
/*162*/	107.3	,
/*163*/	107.7	,
/*164*/	108.1	,
/*165*/	108.5	,
/*166*/	108.9	,
/*167*/	109.3	,
/*168*/	109.7	,
/*169*/	110.1	,
/*170*/	110.5	,
/*171*/	110.9	,
/*172*/	111.3	,
/*173*/	111.7	,
/*174*/	112.1	,
/*175*/	112.5	,
/*176*/	112.9	,
/*177*/	113.3	,
/*178*/	113.7	,
/*179*/	114.1	,
/*180*/	114.5	,
/*181*/	114.9	,
/*182*/	115.3	,
/*183*/	115.7	,
/*184*/	116.1	,
/*185*/	116.5	,
/*186*/	116.9	,
/*187*/	117.3	,
/*188*/	117.7	,
/*189*/	118.1	,
/*190*/	118.5	,
/*191*/	118.9	,
/*192*/	119.3	,
/*193*/	119.7	,
/*194*/	120.1	,
/*195*/	120.5	,
/*196*/	120.9	,
/*197*/	121.3	,
/*198*/	121.7	,
/*199*/	122.1	,
/*200*/	122.5	,
/*201*/	122.9	,
/*202*/	123.3	,
/*203*/	123.7	,
/*204*/	124.1	,
/*205*/	124.5	,
/*206*/	124.9	,
/*207*/	125.3	,
/*208*/	125.7	,
/*209*/	126.1	,
/*210*/	126.5	,
/*211*/	126.9	,
/*212*/	127.3	,
/*213*/	127.7	,
/*214*/	128.1	,
/*215*/	128.5	,
/*216*/	128.9	,
/*217*/	129.3	,
/*218*/	129.7	,
/*219*/	130.1	,
/*220*/	130.5	,
/*221*/	130.9	,
/*222*/	131.3	,
/*223*/	131.7	,
/*224*/	132.1	,
/*225*/	132.5	,
/*226*/	132.9	,
/*227*/	133.3	,
/*228*/	133.7	,
/*229*/	134.1	,
/*230*/	134.5	,
/*231*/	134.9	,
/*232*/	135.3	,
/*233*/	135.7	,
/*234*/	136.1	,
/*235*/	136.5	,
/*236*/	136.9	,
/*237*/	137.3	,
/*238*/	137.7	,
/*239*/	138.1	,
/*240*/	138.5	,
/*241*/	138.9	,
/*242*/	139.3	,
/*243*/	139.7	,
/*244*/	140.1	,
/*245*/	140.5	,
/*246*/	140.9	,
/*247*/	141.3	,
/*248*/	141.7	,
/*249*/	142.1	,
/*250*/	142.5	,
/*251*/	142.9	,
/*252*/	143.3	,
/*253*/	143.7	,
/*254*/	144.1	,
/*255*/	144.5	
    };
  

  return mapr[channel];

}

double dist_TotemT1LG(double x0, double y0, double x1, double y1)
{
  double distance;
  distance = TMath::Sqrt ( (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1) );
  return distance;
}
