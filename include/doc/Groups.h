#ifndef GROUPS_HEADER_INCLUDED
#define GROUPS_HEADER_INCLUDED

/** @defgroup Engine Engine
*
* \brief General components (more or less)
*
* I wanted to make sure I didn't end up "writing an engine", but I wanted to organize game specific code from non-game specific code.
* So in came the engine group.
*
*/

/** @addtogroup Engine */
/*@{*/

  /** @defgroup EngineObjects Objects
  * \brief Components that are used/interacted with in game
  *
  * This group contains objects that are expected to be used and/or attached to in-game components.
  *
  */

  /** @defgroup EngineShapes Shapes
  *
  *
  *
  */

  /** @defgroup EngineUtil Utility
  *
  *
  *
  */

  /** @defgroup EngineFonts Fonts
  *
  *
  *
  */

  /** @defgroup EngineGraphics Graphics
  *
  *
  *
  */

  /** @defgroup EngineContainers Containers
  *
  *
  *
  */
/*@}*/

/** @addtogroup EngineContainers */
/*@{*/
  /** @defgroup EngineIndicesContainers Indices */
  /** @defgroup EngineObjectContainers Objects */
  /** @defgroup EngineIterators Iterators */
/*@}*/

/**
  @defgroup EngineIndicesAuxillary Auxillary
  @ingroup EngineIndicesContainers
*/


/** @defgroup Game Game
*
*
*
*/
/** @addtogroup Game */
/*@{*/

/** @defgroup GameActors Actors
*
*
*
*/

/** @defgroup GameComponents Components
*
*
*
*/

/** @defgroup GameWorld World
*
*
*
*/

/*@}*/

#endif // !GROUPS_HEADER_INCLUDED
