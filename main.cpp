#include"funciones.h"
int main()
{


//---------------------------------ALLEGRO START -------------------------------------------------------------------------------
  ALLEGRO_DISPLAY *display;

  float FPS=60.0;

  if(!al_init())
      {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
      }

  display = al_create_display(X_MAX+10,Y_MAX+10);
  al_set_window_title(display,"R Tree");

  if(!display)
      {
        fprintf(stderr, "failed to create display!\n");
        return -1;
      }
  al_set_window_position(display,200,40);




//--------------------------------INSTANCIAS--------------------------------------
  al_init_image_addon();
  al_install_audio();
  al_init_acodec_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  al_install_keyboard();
  al_init_primitives_addon();

//---------------------------------FUNETES----------------------------------------

 // ALLEGRO_FONT *contador=al_load_font("Alice_in_Wonderland_3.ttf",90,NULL);

//---------------------------------IMAGENES---------------------------------------
/*
  ALLEGRO_BITMAP *brain = al_load_bitmap("Brain.png");
  ALLEGRO_BITMAP *brainburn = al_load_bitmap("Brainburn.png");
  ALLEGRO_BITMAP *fondo = al_load_bitmap("fondo.jpg");
  ALLEGRO_BITMAP *logo = al_load_bitmap("Logo.png");

  for(int i=0;i<cantidad_de_nodos;i++)
    {
      Prueva.Insert(brain);
    }
*/



//-------------------------------CREANDO COLA DE EVENTOS--------------------------

  ALLEGRO_TIMER *timer = al_create_timer(FPS/60);


  ALLEGRO_EVENT_QUEUE *cola_de_eventos = al_create_event_queue();
  ALLEGRO_KEYBOARD_STATE key_state;

  //teclado
  al_register_event_source(cola_de_eventos,al_get_keyboard_event_source());
  al_register_event_source(cola_de_eventos,al_get_timer_event_source(timer));
  al_register_event_source(cola_de_eventos,al_get_display_event_source(display));

//---------------------------------MUSICA--------------------------------
 /* al_reserve_samples(2);

  ALLEGRO_SAMPLE *background = al_load_sample("background.flac");
  ALLEGRO_SAMPLE_INSTANCE *song_instance=al_create_sample_instance(background);
  al_set_sample_instance_position(song_instance,ALLEGRO_PLAYMODE_LOOP);
  al_attach_sample_instance_to_mixer(song_instance,al_get_default_mixer());

  al_play_sample_instance(song_instance);*/

//-------------------------------BUCLE DEL JUEGO----------------------------------

  bool done=false;
  bool drow=false;
  al_start_timer(timer);

  al_clear_to_color(al_map_rgb(255,255,255));//color de fondo
  al_flip_display();

  RTree Rt(8);//M=3
  vector<RTree> Metaservers;
  vector<SN> GraficMetaservers;
  vector<SN> GraficMetaserversLVL1;
  vector<SN> GraficMetaserversLVL3;
  for(int i=0;i<64;i++)
  {
      SN b(make_pair((i%8)+1,(i/8)+1),8);
      GraficMetaserversLVL1.push_back(b);
  }
  for(int i=0;i<16;i++)
  {

      SN b(make_pair((i%4)+1,(i/4)+1),4);
      GraficMetaservers.push_back(b);
  }
  Rt.m_Datos();
  int bound = 30;
  RTree aaa(8);
  Rectangle *AA=new Rectangle(make_pair(0,0),make_pair(300+bound,300+bound));
  RTree bbb(8);
  Rectangle *BB=new Rectangle(make_pair(300-bound,0),make_pair(600+bound,300+bound));
  RTree ccc(8);
  Rectangle *CC=new Rectangle(make_pair(0,300-bound),make_pair(300+bound,600+bound));
  RTree ddd(8);
  Rectangle *DD=new Rectangle(make_pair(300-bound,300-bound),make_pair(600+bound,600+bound));

  Metaservers.push_back(aaa);
  Metaservers.push_back(bbb);
  Metaservers.push_back(ccc);
  Metaservers.push_back(ddd);


  clock_t start = clock();
  rasmus x,xx,y,yy;
  int n=10;


  int cont=0;
  int men=0;
  bool menu=false;
  bool sear=false;
  bool psear=false;
  bool psear1=false;
  bool psear2=false;
  bool psear3=false;
  bool psear4=false;
  bool stop_drow = false;
  bool grafT = false;
  bool gpaper = false;
  bool gmeta1 = false;
  bool gmeta2 = false;
  Rectangle *SSearch;
  bool clean = false;

  while(!done)
    {
      ALLEGRO_EVENT events;

      al_wait_for_event(cola_de_eventos,&events);
      al_get_keyboard_state(&key_state);

      if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
          done=true;
        }

      if(events.type == ALLEGRO_EVENT_TIMER)
        {
          drow = true;
        }
      if(drow && stop_drow ==false)
      {


            //crear rectangulos aleatorios
            /*x=((rand()+start) % 640) - 320;
            y=((rand()+start) % 640) - 320;
            punto a=make_pair(x,y);
            punto b=make_pair(x+10,y+10);
            Rectangle *N=new Rectangle(a,b);
            Rt.Inssert(N);*/

            //contador de rectangulos
            //cont++;
            //cout<<cont<<endl;
            //Descomentar para ingresar datos manualmente
            if(men>2)
            {
                int opcion;
                cout<<"Ingresar opcion"<<endl;
                cout<<"0: salir"<<endl;
                cout<<"1: ingresar un punto o rectangulo"<<endl;
                cout<<"2: busqueda normal"<<endl;
                cout<<"3: ingresar 50 puntos"<<endl;
                cout<<"4: graficar arbol normal"<<endl;
                cout<<"5: graficar HCN lv 1"<<endl;
                cout<<"6: graficar HCN lv 2"<<endl;
                cout<<"7: graficar arbol Paper"<<endl;
                cout<<"8: busqueda Paper"<<endl;
                cout<<"10: limpiar pantalla"<<endl;


                cin>>opcion;
                sear=false;
                psear=false;
                grafT = false;
                gmeta1 = false;
                gmeta2 = false;
                gpaper = false;
                clean = false;
                if(opcion==0){done=true;}
                if(opcion==1)
                {
                    cout<<"|||||||||||||||||||||||||||"<<endl;
                    cout<<"ingrese los datos"<<endl;
                    rasmus a,b,aa,bb;
                    cin>>a;
                    cin>>b;
                    cin>>aa;
                    cin>>bb;
                    Rectangle *N=new Rectangle(make_pair(a,b),make_pair(aa,bb));
                    Rt.Inssert(N);
                }
                if(opcion==2)
                {
                    cout<<"|||||||||||||||||||||||||||"<<endl;
                    cout<<"Ingrese e punto o rectangulo para la busqueda"<<endl;
                    rasmus a,b,aa,bb;
                    cin>>a;
                    cin>>b;
                    cin>>aa;
                    cin>>bb;
                    SSearch=new Rectangle(make_pair(a,b),make_pair(aa,bb));
                    sear=true;
                    psear = false;
                    psear1 = false;
                    psear2 = false;
                    psear3 = false;
                    psear4 = false;
                }
                if(opcion==3)
                {
                    cout<<"|||||||||||||||||||||||||||"<<endl;
                    for(int i=0;i<50;i++)
                    {
                        x=(abs(rand()+start) % 600) ;
                        y=(abs(rand()+start) % 600) ;
                        cout<<"x "<<x<<"  ,  "<<"y "<<y<<endl;
                        punto a=make_pair(x,y);
                        punto b=make_pair(x+10,y+10);
                        Rectangle *N=new Rectangle(a,b);
                        Rt.Inssert(N);
                        if(isInside(AA,a))
                        {
                            aaa.Inssert(N);
                        }
                        if(isInside(BB,a))
                        {
                            bbb.Inssert(N);
                        }
                        if(isInside(CC,a))
                        {
                            ccc.Inssert(N);
                        }
                        if(isInside(DD,a))
                        {
                            ddd.Inssert(N);
                        }
                    }
                }
                if(opcion==4)
                {
                    grafT = true;

                }
                if(opcion==5)
                {
                    gmeta1 = true;
                }
                if(opcion==6)
                {
                    gmeta2 = true;
                }
                if(opcion == 7)
                {
                    gpaper = true;
                }
                if(opcion == 8)
                {
                    cout<<"|||||||||||||||||||||||||||"<<endl;
                    cout<<"Ingrese e punto o rectangulo para la busqueda"<<endl;
                    rasmus a,b,aa,bb;
                    cin>>a;
                    cin>>b;
                    cin>>aa;
                    cin>>bb;
                    SSearch=new Rectangle(make_pair(a,b),make_pair(aa,bb));
                    if(colide(AA,SSearch) or isInside(AA,make_pair(a,b))){psear1 = true;}
                    if(colide(BB,SSearch) or isInside(BB,make_pair(a,b))){psear2 = true;}
                    if(colide(CC,SSearch) or isInside(CC,make_pair(a,b))){psear3 = true;}
                    if(colide(DD,SSearch) or isInside(DD,make_pair(a,b))){psear4 = true;}
                    psear=true;
                }
                if(opcion == 10){clean = true;}
                men=0;
            }
            men++;

            /*if(cont>100)//64 rectangulos aleatorios
            {

                stop_drow = true; //termina el programa
                IndexPublishing(Rt,120,130,120,130);

            }*/



            al_flip_display();
            //IMPRESION
            if(sear)
            {
                Rt.Search(SSearch,Rt.m_head);
            }
            if(psear!=0)
            {
                if(psear1){aaa.Search(SSearch,aaa.m_head);}
                if(psear2){bbb.Search(SSearch,bbb.m_head);}
                if(psear3){ccc.Search(SSearch,ccc.m_head);}
                if(psear4){ddd.Search(SSearch,ddd.m_head);}
            }
            al_draw_line(X_MAX/2,0,X_MAX/2,Y_MAX,al_map_rgb(210,25,16),2);// | eje y
            al_draw_line(0,Y_MAX/2,X_MAX,Y_MAX/2,al_map_rgb(210,25,16),2);// -- eje x

            //al_draw_rectangle(0,0,X_MAX,Y_MAX,al_map_rgb(133,230,234),2);
            //al_draw_rectangle(0,0,X_MAX/2,Y_MAX/2,al_map_rgb(133,230,234),2);
            //al_draw_rectangle(0,0,X_MAX/4,Y_MAX/4,al_map_rgb(133,230,234),2);
            //GraficarServer(3,1);
            //GraficarMetaServer(1,2,2);
            if(grafT)
            {
                Rt.Print(Rt.m_head);
            }

            if(gmeta2)
            {
                for(int i=0;i<GraficMetaservers.size();i++)
                {
                    GraficMetaservers[i].Drow();
                }
            }

            if(gmeta1)
            {
                for(int i=0;i<GraficMetaserversLVL1.size();i++)
                {
                    GraficMetaserversLVL1[i].Drow();
                }
            }
            if(gpaper)
            {
                aaa.Print(aaa.m_head);
                bbb.Print(bbb.m_head);
                ccc.Print(ccc.m_head);
                ddd.Print(ddd.m_head);
            }

            if(clean){al_clear_to_color(al_map_rgb(0,0,0));}
            al_flip_display();
      }

    }






  //al_destroy_font(contador);

  al_destroy_display(display);
  al_destroy_timer(timer);
  al_destroy_event_queue(cola_de_eventos);
  //al_destroy_sample(background);
  //al_destroy_sample_instance(song_instance);


  return 0;

}
