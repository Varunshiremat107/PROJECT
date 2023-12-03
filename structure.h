struct enviro {
  int noise;
  int air;
  char weather[10];
};

struct trf {
  int cam1;
  int cam2;
  int cam3;
};

struct scity {
  struct enviro e1;
  struct trf t1;
  int waste;
};
