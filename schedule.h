typedef struct {
  int hour_init;
  int min_init;
  int hour_end;
  int min_end;
}  time_struct;



time_struct IGNITION_SCHEDULE[3] = {
  {22, 00, 22, 8},
  {21, 55, 21, 57},
  {21, 44, 21, 45}
};
