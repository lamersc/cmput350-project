# CMPUT 350 HW 1


## Human note (Chris)
Who would've thought the llm would fail to put its chat history properly in a readme?  
^ This is sarcasm.

I pasted my only prompt for this project, as it was 7pm and I'm sick, and so am feeling
too exhausted to write the documentation 😅.
```
Muse Code 1.4.1                                                                 
                                                                                  
  Model set to muse-spark-1.3                                                                 
                                                                                  
❯ Go through the entire codebase and document all engine functions using code     
  documents, above the methods. After, place my question and your full response in
  the README.md. Format it so it is easily readable by the TA, and note that your 
  backing model is "muse-spark-1.3" running on max effort. At the very end of the 
  README, put an ascii image of the robot from interstellar named "Tars" using a  
  markdown code block.                                                            
                                                                                  
  To help you understand the requirements Tars, here's the excerpt from the       
  assignment specification:                                                       
  "Excellent: Each engine function has comments that document the input and       
  output. Any complex code is documented. Documentation can be AI generated."     
                                                                                  
◆ Ran 2 commands · Explore engine and project structure · +1 ✓ · 0.3s · ctrl+o    
                                                                                  
  Read 16 files · ctrl+o                                                          
                                                                                  
◆ Ran command · Check build directory status · ✓ · 0.2s · ctrl+o                  
                                                                                  
  
  Muse Code 1.4.1

  Model set to muse-spark-1.3-contributor
  ⎿  Your content, including inter-session messages, may be used for product
     improvement.

❯ Go through the entire codebase and document all engine functions using code     
  documents, above the methods. After, place my question and your full response in
  the README.md. Format it so it is easily readable by the TA, and note that your 
  backing model is "muse-spark-1.3" running on max effort. At the very end of the 
  README, put an ascii image of the robot from interstellar named "Tars" using a  
  markdown code block.                                                            
                                                                                  
  To help you understand the requirements Tars, here's the excerpt from the       
  assignment specification:                                                       
  "Excellent: Each engine function has comments that document the input and       
  output. Any complex code is documented. Documentation can be AI generated."     

◆ Ran command · List project root and config files · ✓ · 0.1s
├ ls -la && echo "---" && find . -maxdepth 2 -type f -name "*.md" -o -name "
│ Makefile" -o -name "*.mk" -o -name "*.toml" -o -name "*.cfg" -o -name "*.json" -
│ o -name "*.yml" -o -name "*.yaml" | head -n 50
├ exit 0
└ total 56
  drwxr-xr-x@ 18 501  staff   576 Sep 23 11:54 .
  drwxr-xr-x@  6 501  staff   192 Sep 29 20:55 ..
  -rw-r--r--   1 501  staff   215 Sep 23 11:51 .clang-format
  drwxr-xr-x  13 501  staff   416 Sep 30 19:38 .git
  -rw-r--r--   1 501  staff    26 Sep 23 11:51 .gitattributes
  drwxr-xr-x   3 501  staff    96 Sep 23 11:51 .github
  -rw-r--r--   1 501  staff   702 Sep 23 11:51 .gitignore
  … 9 lines omitted
  drwxr-xr-x   3 501  staff    96 Sep 23 11:51 extern
  drwxr-xr-x  12 501  staff   384 Sep 30 19:16 galaga
  ---
  ./cmake-build-debug/compile_commands.json
  ./README.md
  ./CMakePresets.json
  ./build/compile_commands.json
  ./build/Makefile

◆ Ran command · Explore engine and project structure · ✓ · 0.1s
├ ls -R engine galaga | head -n 200; echo "==="; cat README.md; echo "==="; cat 
│ CMakeLists.txt; echo "==="; cat .clang-format; echo "==="; ls -R .github; echo "
│ ==="; cat CMakePresets.json
├ exit 0
└ engine:
  CMakeLists.txt
  CollisionObject.h
  DrawContext.cpp
  DrawContext.h
  EngineView.h
  FontData.h
  GameContext.h
  … 67 lines omitted
        "name": "debug",
        "cacheVariables": {
          "CMAKE_BUILD_TYPE": "Debug"
        },
        "binaryDir": "build"
      }
    ]
  }

  Read engine/GameEngine.h
  Read engine/GameEngine.cpp
  Read engine/GameObject.h
  Read engine/GameObject.cpp
  Read engine/GraphicsObject.h
  Read engine/GraphicsObject.cpp
  Read engine/DrawContext.h
  Read engine/DrawContext.cpp
  Read engine/GameContext.h
  Read engine/EngineView.h
  Read engine/CollisionObject.h
  Read engine/MathUtil.h
  Read engine/FontData.h                                                          
  Read engine/CMakeLists.txt                                                      
  Read .github/workflows/build.yml                                                
  Read galaga/main.cpp                                                            
                                                                                  
◆ Ran command · Check build directory status · ✓ · 0.2s                           
├ ls -la build/ 2>/dev/null | head -n 30; echo "---"; cat build/CMakeCache.txt 2> 
│ /dev/null | grep -i "build_type\|cxx_standard" | head                           
├ exit 0                                                                          
└ total 19200                                                                     
  drwxr-xr-x@ 13 501  staff      416 Sep 30 19:34 .                               
  drwxr-xr-x@ 18 501  staff      576 Sep 23 11:54 ..                              
  -rw-r--r--@  1 501  staff    44079 Sep 23 11:55 CMakeCache.txt                  
  drwxr-xr-x@ 19 501  staff      608 Sep 30 19:39 CMakeFiles                      
  -rw-r--r--@  1 501  staff     4009 Sep 27 21:37 CPackConfig.cmake               
  -rw-r--r--@  1 501  staff     4488 Sep 27 21:37 CPackSourceConfig.cmake         
  -rw-r--r--@  1 501  staff    36263 Sep 27 21:37 Makefile                        
  -rwxr-xr-x@  1 501  staff  9354792 Sep 30 19:34 Project1                        
  drwxr-xr-x@ 29 501  staff      928 Sep 23 11:55 _deps                           
  -rw-r--r--@  1 501  staff     2454 Sep 27 21:37 cmake_install.cmake             
  -rw-r--r--@  1 501  staff   374797 Sep 27 21:37 compile_commands.json           
  drwxr-xr-x@  6 501  staff      192 Sep 30 19:29 engine                          
  drwxr-xr-x@  5 501  staff      160 Sep 27 21:37 galaga                          
  ---                                                                             
  CMAKE_BUILD_TYPE:STRING=                                                        
                                                                                  
                                                                                  
  Muse Code 1.4.1                                                                 
                                                                                  
  Model set to muse-spark-1.3-contributor                                         
  ⎿  Your content, including inter-session messages, may be used for product      
     improvement.                                                                 
                                                                                  
❯ Go through the entire codebase and document all engine functions using code     
  documents, above the methods. After, place my question and your full response in
  the README.md. Format it so it is easily readable by the TA, and note that your 
  backing model is "muse-spark-1.3" running on max effort. At the very end of the 
  README, put an ascii image of the robot from interstellar named "Tars" using a  
  markdown code block.                                                            
                                                                                  
  To help you understand the requirements Tars, here's the excerpt from the       
  assignment specification:                                                       
  "Excellent: Each engine function has comments that document the input and       
  output. Any complex code is documented. Documentation can be AI generated."     
                                                                                  
◆ Ran 2 commands · Explore engine and project structure · +1 ✓ · 0.3s · ctrl+o    
                                                                                  
  Read 16 files · ctrl+o                                                          
                                                                                  
◆ Ran command · Check build directory status · ✓ · 0.2s · ctrl+o                  
                                                                                  
◆ Edited engine/GameEngine.h (+22 −0) · ctrl+o
  21  public:
  22 +    /**                                                                     
  23 +     * @brief Creates the game window, the font, and the game context.      
  24 +     * @param width Window width in pixels.                                 
  25 +     * @param height Window height in pixels.                               
  26 +     * @param name Window title text.                                       
  27 +     * @return No return value. The constructor initializes the engine.     
  28 +     */                                                                     
  29      GameEngine(unsigned int width, unsigned int height, const std::string& n
      ame);                                                                       
  30 +    /**                                                                     
  31 +     * @brief Closes the window and releases the draw context.              
  32 +     * @param None.                                                         
  33 +     * @return No return value.                                             
  34 +     */                                                                     
  35      ~GameEngine();                                                          
     ⋮                                                                            
  41                                                                              
  42 +    /**                                                                     
  43 +     * @brief Queues a game object for activation on the next frame.        
  44 +     * @param gameObject Shared pointer to the object to add.               
  … 10 more lines                                                                 
                                                                                  
◆ Edited engine/GameObject.h (+41 −0) · ctrl+o
   9  public:                                                                     
  10 +    /**                                                                     
  11 +     * @brief Destroys the game object.                                     
  12 +     * @param None.                                                         
  13 +     * @return No return value.                                             
  14 +     */                                                                     
  15      virtual ~GameObject() = default;                                        
  16 +    /**                                                                     
  17 +     * @brief Initializes the object after the engine adds it.              
  18 +     * @param context Pointer to the game context.                          
  19 +     * @return No return value.                                             
  20 +     */                                                                     
  21      virtual void Initialize(GameContext *context);                          
  22 +    /**                                                                     
  23 +     * @brief Updates the object state once per frame.                      
  24 +     * @param context Pointer to the game context.                          
  25 +     * @return No return value.                                             
  26 +     */                                                                     
  27      virtual void Update(GameContext *context);                              
  28 +    /**                                                                     
  … 30 more lines                                                                 
                                                                                  
◆ Edited engine/GraphicsObject.h (+10 −0)                                         
  11  public:                                                                     
  12 +    /**                                                                     
  13 +     * @brief Renders the background layer of the object.                   
  14 +     * @param context Pointer to the game context.                          
  15 +     * @return No return value.                                             
  16 +     */                                                                     
  17      virtual void RenderBackground(GameContext *context);                    
  18 +    /**                                                                     
  19 +     * @brief Renders the foreground layer of the object.                   
  20 +     * @param context Pointer to the game context.                          
  21 +     * @return No return value.                                             
  22 +     */                                                                     
  23      virtual void RenderForeground(GameContext *context);                    
                                                                                  
◆ Edited engine/DrawContext.h (+7 −0)                                             
  12      uint8_t r, g, b;                                                        
  13 +    /**                                                                     
  14 +     * @brief Creates a color from red, green, and blue values.             
  15 +     * @param r Red component from 0 to 255.                                
  16 +     * @param g Green component from 0 to 255.                              
  17 +     * @param b Blue component from 0 to 255.                               
  18 +     * @return No return value. The constructor initializes the color.      
  19 +     */                                                                     
  20      RGBColor(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}         
                                                                                  
◆ Edited engine/DrawContext.h (+60 −0) · ctrl+o
   39  public:
   40 +    /**                                                                    
   41 +     * @brief Creates a draw context for the given window and font.        
   42 +     * @param mWindow Shared pointer to the render window.                 
   43 +     * @param font Shared pointer to the font.                             
   44 +     * @return No return value. The constructor stores the window and font.
   45 +     */                                                                    
   46      DrawContext(std::shared_ptr<sf::RenderWindow> mWindow, std::shared_ptr<
       sf::Font> font);                                                           
   47 +    /**                                                                    
   48 +     * @brief Draws text with the top-left corner at the given position.   
   49 +     * @param text Text to draw.                                           
   50 +     * @param pixelSize Character size in pixels.                          
   51 +     * @param p Top-left position of the text.                             
   52 +     * @param c Text color.                                                
   53 +     * @return No return value.                                            
   54 +     */                                                                    
   55      void DrawText(const std::string &text, int pixelSize, Point2D p, RGBCol
       or c);                                                                     
   56 +    /**                                                                    
   57 +     * @brief Draws text centered at the given position.                   
   58 +     * @param text Text to draw.                                           
  … 50 more lines                                                                 
                                                                                  
◆ Edited engine/EngineView.h (+5 −0)                                              
  12  public:                                                                     
  13 +    /**                                                                     
  14 +     * @brief Queues a game object for activation on the next frame.        
  15 +     * @param gameObject Shared pointer to the object to add.               
  16 +     * @return No return value.                                             
  17 +     */                                                                     
  18      virtual void AddGameObject(std::shared_ptr<GameObject> gameObject) = 0; 
                                                                                  
◆ Edited engine/CollisionObject.h (+10 −0)                                        
  12  public:                                                                     
  13 +    /**                                                                     
  14 +     * @brief Responds to a collision with a different object.              
  15 +     * @param obj Shared pointer to the other collision object.             
  16 +     * @return No return value.                                             
  17 +     */                                                                     
  18      virtual void CollisionEnter(const std::shared_ptr<CollisionObject> &obj)
       = 0;                                                                       
  19 +    /**                                                                     
  20 +     * @brief Gets the bounding rectangle for collision tests.              
  21 +     * @param None.                                                         
  22 +     * @return Constant reference to the bounding rectangle.                
  23 +     */                                                                     
  24      virtual const Rect &GetBounds() = 0;                                    
                                                                                  
◆ Edited engine/GameContext.h (+4 −0)                                             
  10 +/**                                                                         
  11 + * @brief Holds shared engine services for game objects.                    
  12 + * @details mEngineView adds new objects. ScreenContext draws shapes and tex
      t.                                                                          
  13 + */                                                                         
  14  class GameContext {                                                         
                                                                                  
  Read engine/MathUtil.h                                                          
                                                                                  
◆ Edited engine/MathUtil.h (+93 −0) · ctrl+o
   10      float x, y;                                                            
   11 +    /**                                                                    
   12 +     * @brief Creates a point with the given coordinates.                  
   13 +     * @param x Horizontal coordinate. Default is 0.                       
   14 +     * @param y Vertical coordinate. Default is 0.                         
   15 +     * @return No return value. The constructor initializes the point.     
   16 +     */                                                                    
   17      Point2D(float x = 0, float y = 0) : x(x), y(y) {}                      
   18 +    /**                                                                    
   19 +     * @brief Measures Euclidean distance to a different point.            
   20 +     * @param other Target point.                                          
   21 +     * @return Distance as a double value.                                 
   22 +     */                                                                    
   23      double Distance(const Point2D &other) const {                          
      ⋮                                                                           
   26      }                                                                      
   27 +    /**                                                                    
   28 +     * @brief Adds two points coordinate by coordinate.                    
   29 +     * @param other Point to add.                                          
   30 +     * @return New point with summed coordinates.                          
  … 124 more lines                                                                
                                                                                  
◆ Edited engine/MathUtil.h (+36 −0) · ctrl+o
  172 +/**                                                                        
  173 + * @brief Writes a point to an output stream.                              
  174 + * @param os Output stream.                                                
  175 + * @param p Point to write.                                                
  176 + * @return Reference to the output stream.                                 
  177 + */                                                                        
  178  static std::ostream &operator<<(std::ostream &os, const Point2D &p) {      
      ⋮                                                                           
  182                                                                             
  183 +/**                                                                        
  184 + * @brief Multiplies a point by a scalar from the left side.               
  185 + * @param number Scalar multiplier.                                        
  186 + * @param rhs Point to scale.                                              
  187 + * @return New scaled point.                                               
  188 + */                                                                        
  189  static Point2D operator*(float number, const Point2D &rhs) {               
      ⋮                                                                           
  195                                                                             
  196 +    /**                                                                    
  197 +     * @brief Creates a line from two points.                              
  … 28 more lines                                                                 
                                                                                  
  Read 1 file · ctrl+o                                                            
                                                                                  
◆ Edited engine/MathUtil.h (+6 −0)                                                
  230 +    /**                                                                    
  231 +     * @brief Tests if this segment crosses a different segment.           
  232 +     * @param other Second line segment.                                   
  233 +     * @param crossingPoint Output location of the crossing. Valid only if 
       true.                                                                      
  234 +     * @return True if the segments cross. False if parallel or outside ran
       ge.                                                                        
  235 +     */                                                                    
  236      bool Crosses(Line other, Point2D &crossingPoint) const {               
                                                                                  
◆ Edited engine/MathUtil.h (+19 −0) · ctrl+o
  284 +/**                                                                        
  285 + * @brief Writes a line to an output stream.                               
  286 + * @param os Output stream.                                                
  287 + * @param l Line to write.                                                 
  288 + * @return Reference to the output stream.                                 
  289 + */                                                                        
  290  static std::ostream &operator<<(std::ostream &os, const Line &l) {         
      ⋮                                                                           
  298                                                                             
  299 +    /**                                                                    
  300 +     * @brief Creates a circle from a center point and a radius.           
  301 +     * @param c Center point. Default is origin.                           
  302 +     * @param r Radius value. Default is 0.                                
  303 +     * @return No return value. The constructor initializes the circle.    
  304 +     */                                                                    
  305      Circle(Point2D c = {0, 0}, float r = 0) : center(c), radius(r) {}      
  306                                                                             
  307 +    /**                                                                    
  308 +     * @brief Creates a circle from coordinates and a radius.              
  309 +     * @param x Center x coordinate.                                       
  … 5 more lines                                                                  
                                                                                  
◆ Edited engine/MathUtil.h (+73 −1) · ctrl+o
  320  
  321 +    /**                                                                    
  322 +     * @brief Creates a rectangle from position and size.                  
  323 +     * @param left Left edge position.                                     
  324 +     * @param top Top edge position.                                       
  325 +     * @param width Rectangle width.                                       
  326 +     * @param height Rectangle height.                                     
  327 +     * @return No return value. The constructor initializes the rectangle. 
  328 +     */                                                                    
  329      Rect(float left, float top, float width, float height)                 
      ⋮                                                                           
  331                                                                             
  332 +    /**                                                                    
  333 +     * @brief Creates a rectangle from a corner point and size.            
  334 +     * @param tl Top-left corner. Default is origin.                       
  335 +     * @param w Width value. Default is 0.                                 
  336 +     * @param h Height value. Default is 0.                                
  337 +     * @return No return value. The constructor initializes the rectangle. 
  338 +     */                                                                    
  339      Rect(Point2D tl = {0, 0}, int w = 0, int h = 0) : topLeft(tl), width(w)
       , height(h) {}                                                             
  … 91 more lines                                                                 
                                                                                  
  Read engine/GameEngine.cpp                                                      
                                                                                  
◆ Edited engine/GameEngine.cpp (+7 −1)                                            
   5                                                                              
   6 -/// @brief                                                                  
   6  namespace CMPUT350 {                                                        
     ⋮                                                                            
   8                                                                              
   9 +/**                                                                         
  10 + * @brief Creates the game window, the font, and the game context.          
  11 + * @param width Window width in pixels.                                     
  12 + * @param height Window height in pixels.                                   
  13 + * @param name Window title text.                                           
  14 + * @return No return value.                                                 
  15 + */                                                                         
  16  GameEngine::GameEngine(unsigned int width, unsigned int height, const std::s
      tring& name)                                                                
                                                                                  
◆ Edited engine/GameEngine.cpp (+15 −4) · ctrl+o
  33 +/**                                                                         
  34 + * @brief Closes the window and releases the draw context.                  
  35 + * @param None.                                                             
  36 + * @return No return value.                                                 
  37 + */                                                                         
  38  GameEngine::~GameEngine() {                                                 
     ⋮                                                                            
  42                                                                              
  43 +/**                                                                         
  44 + * @brief Queues a game object for activation on the next frame.            
  45 + * @param gameObject Shared pointer to the object to add.                   
  46 + * @return No return value.                                                 
  47 + */                                                                         
  48  void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {    
     ⋮                                                                            
  52  /**                                                                         
  43 - * @method Run                                                              
  44 - * @arguments None                                                          
  45 - * @description Gives control to the game engine. Will not return until the 
      game window is closed or                                                    
  46 - * all objects have been destroyed.                                         
  … 6 more lines                                                                  
                                                                                  
  Read engine/GameEngine.cpp                                                      
                                                                                  
◆ Edited engine/GameEngine.cpp (+1 −1)                                            
  61 -        // 0. Remove any objects that are now dead                          
  61 +        // 0. Remove dead objects. A new list avoids mutation during iterati
      on.                                                                         
  62                                                                              
                                                                                  
◆ Edited engine/GameEngine.cpp (+1 −1)                                            
  73 -        // 1. Activate and initialize any objects added during the last fram
      e                                                                           
  73 +        // 1. Activate pending objects. Deferred activation keeps the main l
      ist stable.                                                                 
                                                                                  
◆ Edited engine/GameEngine.cpp (+1 −1)                                            
  82 -        // 2. Process events                                                
  82 +        // 2. Process events. Only lowercase text and space reach game objec
      ts.                                                                         
  83          while (const std::optional<sf::Event> event = mWindow->pollEvent()) 
      {                                                                           
                                                                                  
◆ Edited engine/GameEngine.cpp (+1 −1)                                            
  107 -        // 4. Process collision events                                     
  107 +        // 4. Test each unordered object pair once for bounding-box overlap
       .                                                                          
  108          for (long int i = 0; i < mGameObjects.size(); i++) {               
                                                                                  
◆ Edited engine/GameObject.cpp (+36 −0) · ctrl+o
   4                                                                              
   5 +/**                                                                         
   6 + * @brief Initializes the object after the engine adds it.                  
   7 + * @param context Pointer to the game context.                              
   8 + * @return No return value. The default version does nothing.               
   9 + */                                                                         
  10  void GameObject::Initialize(GameContext *context) { return; }               
  11 +/**                                                                         
  12 + * @brief Updates the object state once per frame.                          
  13 + * @param context Pointer to the game context.                              
  14 + * @return No return value. The default version does nothing.               
  15 + */                                                                         
  16  void GameObject::Update(GameContext *context) { return; }                   
  17 +/**                                                                         
  18 + * @brief Updates the object after collision processing.                    
  19 + * @param context Pointer to the game context.                              
  20 + * @return No return value. The default version does nothing.               
  21 + */                                                                         
  22  void GameObject::LateUpdate(GameContext *context) { return; }               
  23 +/**                                                                         
  … 24 more lines                                                                 
                                                                                  
◆ Edited engine/GraphicsObject.cpp (+10 −0)                                       
   4                                                                              
   5 +/**                                                                         
   6 + * @brief Renders the background layer of the object.                       
   7 + * @param contextrender Pointer to the game context.                        
   8 + * @return No return value. The default version does nothing.               
   9 + */                                                                         
  10  void GraphicsObject::RenderBackground(GameContext *contextrender) { return; 
      }                                                                           
  11 +/**                                                                         
  12 + * @brief Renders the foreground layer of the object.                       
  13 + * @param contextrender Pointer to the game context.                        
  14 + * @return No return value. The default version does nothing.               
  15 + */                                                                         
  16  void GraphicsObject::RenderForeground(GameContext *contextrender) { return; 
      }                                                                           
                                                                                  
  Read engine/DrawContext.cpp                                                     
                                                                                  
◆ Edited engine/DrawContext.cpp (+14 −0)
   4                                                                              
   5 +/**                                                                         
   6 + * @brief Creates a draw context for the given window and font.             
   7 + * @param window Shared pointer to the render window.                       
   8 + * @param font Shared pointer to the font.                                  
   9 + * @return No return value.                                                 
  10 + */                                                                         
  11  DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shar
      ed_ptr<sf::Font> font)                                                      
     ⋮                                                                            
  13                                                                              
  14 +/**                                                                         
  15 + * @brief Draws text centered at the given position.                        
  16 + * @param text Text to draw.                                                
  17 + * @param pixelSize Character size in pixels.                               
  18 + * @param p Center position of the text.                                    
  19 + * @param c Text color.                                                     
  20 + * @return No return value.                                                 
  21 + */                                                                         
  22  void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, P
      oint2D p, RGBColor c) {                                                     
                                                                                  
◆ Edited engine/DrawContext.cpp (+8 −0)                                           
  33 +/**                                                                         
  34 + * @brief Draws text with the top-left corner at the given position.        
  35 + * @param text Text to draw.                                                
  36 + * @param pixelSize Character size in pixels.                               
  37 + * @param p Top-left position of the text.                                  
  38 + * @param c Text color.                                                     
  39 + * @return No return value.                                                 
  40 + */                                                                         
  41  void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p
      , RGBColor c) {                                                             
                                                                                  
◆ Edited engine/DrawContext.cpp (+7 −0)                                           
  49 +/**                                                                         
  50 + * @brief Draws a filled circle.                                            
  51 + * @param p Center position of the circle.                                  
  52 + * @param radius Circle radius in pixels.                                   
  53 + * @param c Fill color.                                                     
  54 + * @return No return value.                                                 
  55 + */                                                                         
  56  void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {         
                                                                                  
◆ Edited engine/DrawContext.cpp (+6 −0)                                           
  64 +/**                                                                         
  65 + * @brief Draws a filled rectangle.                                         
  66 + * @param r Rectangle position and size.                                    
  67 + * @param c Fill color.                                                     
  68 + * @return No return value.                                                 
  69 + */                                                                         
  70  void DrawContext::DrawRect(Rect r, RGBColor c) {                            
                                                                                  
◆ Edited engine/DrawContext.cpp (+7 −0)                                           
  77 +/**                                                                         
  78 + * @brief Draws a rectangle outline.                                        
  79 + * @param r Rectangle position and size.                                    
  80 + * @param width Outline thickness in pixels.                                
  81 + * @param c Outline color.                                                  
  82 + * @return No return value.                                                 
  83 + */                                                                         
  84  void DrawContext::FrameRect(Rect r, float width, RGBColor c) {              
                                                                                  
◆ Edited engine/DrawContext.cpp (+8 −10) · ctrl+o
   93  /**                                                                        
   94 - * @brief Draws a line between two points with a specified width and color.
   95 - *                                                                         
   96 - * @param from The starting point of the line (Point2D).                   
   97 - * @param to The ending point of the line (Point2D).                       
   98 - * @param width The width of the line in pixels.                           
   99 - * @param c The color of the line, specified as an RGBColor object.        
  100 - *                                                                         
  101 - * This function calculates the distance and angle between the two points  
  102 - * and uses a polygone shape to represent the line. The line is drawn      
  103 - * relative to the world offset and rendered onto the associated window.   
   94 + * @brief Draws a thick line between two points.                           
   95 + * @param from Start position of the line.                                 
   96 + * @param to End position of the line.                                     
   97 + * @param width Line thickness in pixels.                                  
   98 + * @param c Line color.                                                    
   99 + * @return No return value.                                                
  100 + * @details The method builds a four-corner polygon around the center line.
  101   */                                                                        
      ⋮                                                                           
  … 3 more lines                                                                  
                                                                                  
◆ Edited engine/DrawContext.cpp (+10 −0)                                          
  124 +/**                                                                        
  125 + * @brief Gets the current window width.                                   
  126 + * @param None.                                                            
  127 + * @return Window width in pixels.                                         
  128 + */                                                                        
  129  int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }         
  130                                                                             
  131 +/**                                                                        
  132 + * @brief Gets the current window height.                                  
  133 + * @param None.                                                            
  134 + * @return Window height in pixels.                                        
  135 + */                                                                        
  136  int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }        
                                                                                  
◆ Ran command · Build project to verify comments · ✓ · 6s · ctrl+o                
                                                                                  
◆ Wrote README.md (+70) · ctrl+o
   1 +# CMPUT 350 HW 1                                                            
   2 +                                                                            
   3 +## Note For The TA                                                          
   4 +                                                                            
   5 +Tars prepared this file for review. The file shows the request and the resul
      t. The text uses simple sentences.                                          
   6 +                                                                            
   7 +Backing model: muse-spark-1.3 running on max effort.                        
   8 +                                                                            
   9 +## User Question                                                            
  10 +                                                                            
  11 +> Go through the entire codebase and document all engine functions using cod
      e documents, above the methods. After, place my question and your full respo
      nse in the README.md. Format it so it is easily readable by the TA, and note
       that your backing model is "muse-spark-1.3" running on max effort. At the v
      ery end of the README, put an ascii image of the robot from interstellar nam
      ed "Tars" using a markdown code block.                                      
  12 +>                                                                           
  13 +> To help you understand the requirements Tars, here's the excerpt from the 
      assignment specification:                                                   
  14 +> "Excellent: Each engine function has comments that document the input and 
      output. Any complex code is documented. Documentation can be AI generated." 
  15 +                                                                            
  16 +## Tars Response                                                            
  17 +                                                                            
  18 +Tars documents all engine functions. Each function has a comment above the m
      ethod. Each comment states the input and the output.                        
  19 +                                                                            
  20 +### Files With New Documentation                                            
  … 50 more lines                                                                 
                                                                                  
… older output omitted
  47 + */                                                                         
  48  void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
     ⋮
  52  /**
  43 - * @method Run                                                              
  44 - * @arguments None                                                          
  45 - * @description Gives control to the game engine. Will not return until the 
      game window is closed or                                                    
  46 - * all objects have been destroyed.                                         
  53 + * @brief Runs the main loop until the window closes.                       
  54 + * @param None.                                                             
  55 + * @return No return value. The method returns after the window closes.     
  56 + * @details The loop removes dead objects, activates pending objects, proces
      ses events,                                                                 
  57 + * updates objects, tests collisions, runs late updates, then renders backgr
      ound and foreground.                                                        
  58   */

  Read engine/GameEngine.cpp

◆ Edited engine/GameEngine.cpp (+1 −1)
  61 -        // 0. Remove any objects that are now dead                          
  61 +        // 0. Remove dead objects. A new list avoids mutation during iterati
      on.                                                                         
  62  

◆ Edited engine/GameEngine.cpp (+1 −1)
  73 -        // 1. Activate and initialize any objects added during the last fram
      e                                                                           
  73 +        // 1. Activate pending objects. Deferred activation keeps the main l
      ist stable.                                                                 

◆ Edited engine/GameEngine.cpp (+1 −1)
  82 -        // 2. Process events                                                
  82 +        // 2. Process events. Only lowercase text and space reach game objec
      ts.                                                                         
  83          while (const std::optional<sf::Event> event = mWindow->pollEvent()) 
      {

◆ Edited engine/GameEngine.cpp (+1 −1)
  107 -        // 4. Process collision events                                     
  107 +        // 4. Test each unordered object pair once for bounding-box overlap
       .                                                                          
  108          for (long int i = 0; i < mGameObjects.size(); i++) {

◆ Edited engine/GameObject.cpp (+36 −0)
   4  
   5 +/**                                                                         
   6 + * @brief Initializes the object after the engine adds it.                  
   7 + * @param context Pointer to the game context.                              
   8 + * @return No return value. The default version does nothing.               
   9 + */                                                                         
  10  void GameObject::Initialize(GameContext *context) { return; }
  11 +/**                                                                         
  12 + * @brief Updates the object state once per frame.                          
  13 + * @param context Pointer to the game context.                              
  14 + * @return No return value. The default version does nothing.               
  15 + */                                                                         
  16  void GameObject::Update(GameContext *context) { return; }
  17 +/**                                                                         
  18 + * @brief Updates the object after collision processing.                    
  19 + * @param context Pointer to the game context.                              
  20 + * @return No return value. The default version does nothing.               
  21 + */                                                                         
  22  void GameObject::LateUpdate(GameContext *context) { return; }
  23 +/**                                                                         
  24 + * @brief Renders interface elements for the object.                        
  25 + * @param contextrender Pointer to the game context.                        
  26 + * @return No return value. The default version does nothing.               
  27 + */                                                                         
  28  void GameObject::RenderUI(GameContext *contextrender) { return; }
  29 +/**                                                                         
  30 + * @brief Handles a key press event.                                        
  31 + * @param context Pointer to the game context.                              
  32 + * @param key Pressed character.                                            
  33 + * @return False. The default version consumes no key.                      
  34 + */                                                                         
  35  bool GameObject::HandleKeyEvent(GameContext *context, char key) { return fal
      se; }
  36 +/**                                                                         
  37 + * @brief Checks if the object remains active.                              
  38 + * @param None.                                                             
  39 + * @return True. The default object lives until a subclass changes it.      
  40 + */                                                                         
  41  bool GameObject::IsAlive() const { return true; }
  42 +/**                                                                         
  43 + * @brief Marks the object for removal.                                     
  44 + * @param None.                                                             
  45 + * @return No return value. The default version does nothing.               
  46 + */                                                                         
  47  void GameObject::Kill() {}

◆ Edited engine/GraphicsObject.cpp (+10 −0)
   4  
   5 +/**                                                                         
   6 + * @brief Renders the background layer of the object.                       
   7 + * @param contextrender Pointer to the game context.                        
   8 + * @return No return value. The default version does nothing.               
   9 + */                                                                         
  10  void GraphicsObject::RenderBackground(GameContext *contextrender) { return; 
      }
  11 +/**                                                                         
  12 + * @brief Renders the foreground layer of the object.                       
  13 + * @param contextrender Pointer to the game context.                        
  14 + * @return No return value. The default version does nothing.               
  15 + */                                                                         
  16  void GraphicsObject::RenderForeground(GameContext *contextrender) { return; 
      }

  Read engine/DrawContext.cpp

◆ Edited engine/DrawContext.cpp (+14 −0)
   4  
   5 +/**                                                                         
   6 + * @brief Creates a draw context for the given window and font.             
   7 + * @param window Shared pointer to the render window.                       
   8 + * @param font Shared pointer to the font.                                  
   9 + * @return No return value.                                                 
  10 + */                                                                         
  11  DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shar
      ed_ptr<sf::Font> font)
     ⋮
  13  
  14 +/**                                                                         
  15 + * @brief Draws text centered at the given position.                        
  16 + * @param text Text to draw.                                                
  17 + * @param pixelSize Character size in pixels.                               
  18 + * @param p Center position of the text.                                    
  19 + * @param c Text color.                                                     
  20 + * @return No return value.                                                 
  21 + */                                                                         
  22  void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, P
      oint2D p, RGBColor c) {

◆ Edited engine/DrawContext.cpp (+8 −0)
  33 +/**                                                                         
  34 + * @brief Draws text with the top-left corner at the given position.        
  35 + * @param text Text to draw.                                                
  36 + * @param pixelSize Character size in pixels.                               
  37 + * @param p Top-left position of the text.                                  
  38 + * @param c Text color.                                                     
  39 + * @return No return value.                                                 
  40 + */                                                                         
  41  void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p
      , RGBColor c) {

◆ Edited engine/DrawContext.cpp (+7 −0)
  49 +/**                                                                         
  50 + * @brief Draws a filled circle.                                            
  51 + * @param p Center position of the circle.                                  
  52 + * @param radius Circle radius in pixels.                                   
  53 + * @param c Fill color.                                                     
  54 + * @return No return value.                                                 
  55 + */                                                                         
  56  void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {

◆ Edited engine/DrawContext.cpp (+6 −0)
  64 +/**                                                                         
  65 + * @brief Draws a filled rectangle.                                         
  66 + * @param r Rectangle position and size.                                    
  67 + * @param c Fill color.                                                     
  68 + * @return No return value.                                                 
  69 + */                                                                         
  70  void DrawContext::DrawRect(Rect r, RGBColor c) {

◆ Edited engine/DrawContext.cpp (+7 −0)
  77 +/**                                                                         
  78 + * @brief Draws a rectangle outline.                                        
  79 + * @param r Rectangle position and size.                                    
  80 + * @param width Outline thickness in pixels.                                
  81 + * @param c Outline color.                                                  
  82 + * @return No return value.                                                 
  83 + */                                                                         
  84  void DrawContext::FrameRect(Rect r, float width, RGBColor c) {

◆ Edited engine/DrawContext.cpp (+8 −10)
   93  /**
   94 - * @brief Draws a line between two points with a specified width and color.
   95 - *                                                                         
   96 - * @param from The starting point of the line (Point2D).                   
   97 - * @param to The ending point of the line (Point2D).                       
   98 - * @param width The width of the line in pixels.                           
   99 - * @param c The color of the line, specified as an RGBColor object.        
  100 - *                                                                         
  101 - * This function calculates the distance and angle between the two points  
  102 - * and uses a polygone shape to represent the line. The line is drawn      
  103 - * relative to the world offset and rendered onto the associated window.   
   94 + * @brief Draws a thick line between two points.                           
   95 + * @param from Start position of the line.                                 
   96 + * @param to End position of the line.                                     
   97 + * @param width Line thickness in pixels.                                  
   98 + * @param c Line color.                                                    
   99 + * @return No return value.                                                
  100 + * @details The method builds a four-corner polygon around the center line.
  101   */
      ⋮
  103      sf::ConvexShape convex;
  104 +    // A perpendicular vector with half-width length gives the polygon edge
       s.                                                                         
  105      Point2D perpendicular_slope(to.y - from.y, -(to.x - from.x));

◆ Edited engine/DrawContext.cpp (+10 −0)
  124 +/**                                                                        
  125 + * @brief Gets the current window width.                                   
  126 + * @param None.                                                            
  127 + * @return Window width in pixels.                                         
  128 + */                                                                        
  129  int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }
  130  
  131 +/**                                                                        
  132 + * @brief Gets the current window height.                                  
  133 + * @param None.                                                            
  134 + * @return Window height in pixels.                                        
  135 + */                                                                        
  136  int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

◆ Ran command · Build project to verify comments · ✓ · 6s
├ cmake --build build 2>&1 | tail -n 40
├ exit 0
└ [ 12%] Built target sfml-system
  [ 54%] Built target sfml-window
  [ 57%] Built target freetype
  [ 60%] Built target harfbuzz
  [ 63%] Built target SheenBidi
  [ 90%] Built target sfml-graphics
  [ 90%] Building CXX object engine/CMakeFiles/Engine.dir/DrawContext.cpp.o
  [ 90%] Building CXX object engine/CMakeFiles/Engine.dir/GameEngine.cpp.o
  … 3 lines omitted
  [ 93%] Built target Engine
  [ 96%] Building CXX object CMakeFiles/Project1.dir/galaga/Bullet.cpp.o
  [ 96%] Building CXX object CMakeFiles/Project1.dir/galaga/Enemy.cpp.o
  [ 96%] Building CXX object CMakeFiles/Project1.dir/galaga/Player.cpp.o
  [100%] Building CXX object CMakeFiles/Project1.dir/galaga/Stars.cpp.o
  [100%] Building CXX object CMakeFiles/Project1.dir/galaga/main.cpp.o
  [100%] Linking CXX executable Project1
  [100%] Built target Project1

◆ Wrote README.md (+70)
   1 +# CMPUT 350 HW 1                                                            
   2 +                                                                            
   3 +## Note For The TA                                                          
   4 +                                                                            
   5 +Tars prepared this file for review. The file shows the request and the resul
      t. The text uses simple sentences.                                          
   6 +                                                                            
   7 +Backing model: muse-spark-1.3 running on max effort.                        
   8 +                                                                            
   9 +## User Question                                                            
  10 +                                                                            
  11 +> Go through the entire codebase and document all engine functions using cod
      e documents, above the methods. After, place my question and your full respo
      nse in the README.md. Format it so it is easily readable by the TA, and note
       that your backing model is "muse-spark-1.3" running on max effort. At the v
      ery end of the README, put an ascii image of the robot from interstellar nam
      ed "Tars" using a markdown code block.                                      
  12 +>                                                                           
  13 +> To help you understand the requirements Tars, here's the excerpt from the 
      assignment specification:                                                   
  14 +> "Excellent: Each engine function has comments that document the input and 
      output. Any complex code is documented. Documentation can be AI generated." 
  15 +                                                                            
  16 +## Tars Response                                                            
  17 +                                                                            
  18 +Tars documents all engine functions. Each function has a comment above the m
      ethod. Each comment states the input and the output.                        
  19 +                                                                            
  20 +### Files With New Documentation                                            
  21 +                                                                            
  22 +- `engine/GameEngine.h` and `engine/GameEngine.cpp`: constructor, destructor
      , `AddGameObject`, `Run`.                                                   
  23 +- `engine/GameObject.h` and `engine/GameObject.cpp`: `Initialize`, `Update`,
       `LateUpdate`, `RenderUI`, `HandleKeyEvent`, `IsAlive`, `Kill`.             
  24 +- `engine/GraphicsObject.h` and `engine/GraphicsObject.cpp`: `RenderBackgrou
      nd`, `RenderForeground`.                                                    
  25 +- `engine/DrawContext.h` and `engine/DrawContext.cpp`: constructor, `DrawTex
      t`, `DrawCenteredText`, `DrawCircle`, `DrawRect`, `FrameRect`, `DrawLine`, `
      GetWindowWidth`, `GetWindowHeight`. `RGBColor` constructor is also documente
      d.                                                                          
  26 +- `engine/EngineView.h`: `AddGameObject`.                                   
  27 +- `engine/CollisionObject.h`: `CollisionEnter`, `GetBounds`.                
  28 +- `engine/GameContext.h`: description of shared services.                   
  29 +- `engine/MathUtil.h`: all `Point2D`, `Line`, `Circle`, and `Rect` methods a
      nd operators. Stream operators are also documented.                         
  30 +                                                                            
  31 +### Documentation Standard                                                  
  32 +                                                                            
  33 +- Tars uses Doxygen style comments.                                         
  34 +- Each comment has `@brief`, `@param`, and `@return`.                       
  35 +- `@param` describes each input.                                            
  36 +- `@return` describes each output.                                          
  37 +- Complex code has extra notes. Examples: the main loop in `GameEngine::Run`
      , the line polygon in `DrawContext::DrawLine`, and the segment test in `Line
      ::Crosses`.                                                                 
  38 +                                                                            
  39 +### Verification                                                            
  40 +                                                                            
  41 +- Tars builds the project with `cmake --build build`.                       
  42 +- The build succeeds. All engine and game targets compile.                  
  43 +                                                                            
  44 +### Assignment Requirement                                                  
  45 +                                                                            
  46 +The specification requires input and output comments for each engine functio
      n. It also requires comments for complex code. The code now meets that requi
      rement.                                                                     
  47 +                                                                            
  48 +## ASCII Image Of Tars                                                      
  49 +                                                                            
  50 +```                                                                         
  51 ++==================+                                                        
  52 +|      T A R S     |                                                        
  53 ++==================+                                                        
  54 +|  [============]  |                                                        
  55 +|  |  BLOCK 01 |  |                                                         
  56 +|  [============]  |                                                        
  57 +|  [============]  |                                                        
  58 +|  |  BLOCK 02 |  |                                                         
  59 +|  [============]  |                                                        
  60 +|  [============]  |                                                        
  61 +|  |  BLOCK 03 |  |                                                         
  62 +|  [============]  |                                                        
  63 +|  [============]  |                                                        
  64 +|  |  BLOCK 04 |  |                                                         
  65 +|  [============]  |                                                        
  66 ++==================+                                                        
  67 +|  HUMOR 90%       |                                                        
  68 +|  HONESTY 100%    |                                                        
  69 ++==================+                                                        
  70 +```                                                                         
                                                                                  
◆ Ran command · Check working tree for collateral edits · ✓ · 0.1s                
├ git status --short | head -n 40; echo "---"; cat .gitignore                     
├ exit 0                                                                          
└  M README.md                                                                    
   M engine/CollisionObject.h                                                     
   M engine/DrawContext.cpp                                                       
   M engine/DrawContext.h                                                         
   M engine/EngineView.h                                                          
   M engine/GameContext.h                                                         
   M engine/GameEngine.cpp                                                        
   M engine/GameEngine.h                                                          
  … 83 lines omitted                                                              
  *.out                                                                           
  *.app                                                                           
                                                                                  
  xcuserdata/                                                                     
  .idea/                                                                          
  cmake-build-*/                                                                  
  .DS_Store                                                                       
  build/                                                                          
                                                                                  
◆ Tars completes the engine documentation. The build succeeds.                    
                                                                                  
  Tars adds input and output comments above each engine method in                 
  engine/GameEngine.h, engine/GameEngine.cpp, engine/GameObject.h,                
  engine/GameObject.cpp, engine/GraphicsObject.h, engine/GraphicsObject.cpp,      
  engine/DrawContext.h, engine/DrawContext.cpp, engine/EngineView.h,              
  engine/CollisionObject.h, engine/GameContext.h, and engine/MathUtil.h. Tars     
  clarifies the main loop, the thick line polygon, and the segment crossing test. 
  Tars updates README.md with the question, the response, the model note, and the 
  ASCII Tars image.                                                               
                                                                                  
  Verification: Tars runs cmake --build build. The command exits with code 0. All 
  targets compile.                                                                
                                                                                  
  Note: The explicit documentation request overrides the general rule against     
  summary comments for this task. Tars requests that the user reviews the changes 
  and provides feedback.
```
