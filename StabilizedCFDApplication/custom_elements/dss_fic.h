//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Jordi Cotela
//


#ifndef KRATOS_DSS_FIC_H
#define KRATOS_DSS_FIC_H

#include "includes/define.h"
#include "includes/serializer.h"
#include "geometries/geometry.h"

#include "stabilized_cfd_application_variables.h"
#include "custom_elements/dss.h"
#include "../FluidDynamicsApplication/fluid_dynamics_application_variables.h"


namespace Kratos
{

///@addtogroup StabilizedCFDApplication
///@{

///@name Kratos Globals
///@{

///@}
///@name Type Definitions
///@{

///@}
///@name  Enum's
///@{

///@}
///@name  Functions
///@{

///@}
///@name Kratos Classes
///@{

template< unsigned int TDim >
class DSS_FIC : public DSS<TDim>
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of DSS
    KRATOS_CLASS_POINTER_DEFINITION(DSS_FIC);

    /// Node type (default is: Node<3>)
    typedef Node<3> NodeType;

    /// Geometry type (using with given NodeType)
    typedef Geometry<NodeType> GeometryType;

    /// Definition of nodes container type, redefined from GeometryType
    typedef Geometry<NodeType>::PointsArrayType NodesArrayType;

    /// Vector type for local contributions to the linear system
    typedef Vector VectorType;

    /// Matrix type for local contributions to the linear system
    typedef Matrix MatrixType;

    typedef std::size_t IndexType;

    typedef std::size_t SizeType;

    typedef std::vector<std::size_t> EquationIdVectorType;

    typedef std::vector< Dof<double>::Pointer > DofsVectorType;

    typedef PointerVectorSet<Dof<double>, IndexedObject> DofsArrayType;

    /// Type for shape function values container
    typedef Kratos::Vector ShapeFunctionsType;

    /// Type for a matrix containing the shape function gradients
    typedef Kratos::Matrix ShapeFunctionDerivativesType;

    /// Type for an array of shape function gradient matrices
    typedef GeometryType::ShapeFunctionsGradientsType ShapeFunctionDerivativesArrayType;

    typedef Element::PropertiesType PropertiesType;

    ///@}
    ///@name Life Cycle
    ///@{

    //Constructors.

    /// Default constuctor.
    /**
     * @param NewId Index number of the new element (optional)
     */
    DSS_FIC(IndexType NewId = 0);

    /// Constructor using an array of nodes.
    /**
     * @param NewId Index of the new element
     * @param ThisNodes An array containing the nodes of the new element
     */
    DSS_FIC(IndexType NewId, const NodesArrayType& ThisNodes);

    /// Constructor using a geometry object.
    /**
     * @param NewId Index of the new element
     * @param pGeometry Pointer to a geometry object
     */
    DSS_FIC(IndexType NewId, GeometryType::Pointer pGeometry);

    /// Constuctor using geometry and properties.
    /**
     * @param NewId Index of the new element
     * @param pGeometry Pointer to a geometry object
     * @param pProperties Pointer to the element's properties
     */
    DSS_FIC(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties);

    /// Destructor.
    virtual ~DSS_FIC();

    ///@}
    ///@name Operators
    ///@{


    ///@}
    ///@name Operations
    ///@{


    /// Create a new element of this type
    /**
     * Returns a pointer to a new DSS element, created using given input
     * @param NewId: the ID of the new element
     * @param ThisNodes: the nodes of the new element
     * @param pProperties: the properties assigned to the new element
     * @return a Pointer to the new element
     */
    Element::Pointer Create(IndexType NewId,
                            NodesArrayType const& ThisNodes,
                            PropertiesType::Pointer pProperties) const override;


    void CalculateMassMatrix(MatrixType &rMassMatrix, ProcessInfo &rCurrentProcessInfo) override;

    ///@}

protected:

    ///@name Protected static Member Variables
    ///@{


    ///@}
    ///@name Protected member Variables
    ///@{


    ///@}
    ///@name Protected Operators
    ///@{


    ///@}
    ///@name Protected Operations
    ///@{


    virtual void CalculateStabilizationParameters(double Density,
                                    double KinematicVisc,
                                    const array_1d<double,3> &Velocity,
                                    const ProcessInfo& rProcessInfo,
                                    double &TauIncompr,
                                    double &TauMomentum,
                                    array_1d<double,3> &TauGrad);

    virtual void CalculateTauGrad(array_1d<double,3>& TauGrad);


    virtual void AddSystemTerms(unsigned int GaussIndex,
                                double GaussWeight,
                                const ShapeFunctionsType& rN,
                                const ShapeFunctionDerivativesType& rDN_DX,
                                const ProcessInfo& rProcessInfo,
                                MatrixType& rLHS,
                                VectorType& rRHS) override;



    virtual void AddMassStabilization(unsigned int GaussIndex,
                                      double GaussWeight,
                                      const ShapeFunctionsType& rN,
                                      const ShapeFunctionDerivativesType& rDN_DX,
                                      const ProcessInfo& rProcessInfo,
                                      MatrixType& rMassMatrix) override;


    virtual double AverageElementSize();

    virtual double ProjectedElementSize(const array_1d<double,3> &rVelocity);


    double Module(const array_1d<double,3> &rVector);

    void Normalize(array_1d<double,3> &rVector);

    double ProjectedSizeHexa(const array_1d<double,3> &rDirection);


    ///@}
    ///@name Protected  Access
    ///@{


    ///@}
    ///@name Protected Inquiry
    ///@{


    ///@}
    ///@name Protected LifeCycle
    ///@{


    ///@}

private:

    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    ///@}
    ///@name Serialization
    ///@{

    friend class Serializer;

    void save(Serializer& rSerializer) const override;

    void load(Serializer& rSerializer) override;

    ///@}
    ///@name Private Operators
    ///@{


    ///@}
    ///@name Private Operations
    ///@{


    ///@}
    ///@name Private  Access
    ///@{


    ///@}
    ///@name Private Inquiry
    ///@{


    ///@}
    ///@name Un accessible methods
    ///@{

    /// Assignment operator.
    DSS_FIC& operator=(DSS_FIC const& rOther);

    /// Copy constructor.
    DSS_FIC(DSS_FIC const& rOther);

    ///@}


}; // Class DSS

///@}

///@name Type Definitions
///@{


///@}
///@name Input and output
///@{


/// input stream function
template< unsigned int TDim >
inline std::istream& operator >>(std::istream& rIStream,
                                 DSS_FIC<TDim>& rThis)
{
    return rIStream;
}

/// output stream function
template< unsigned int TDim >
inline std::ostream& operator <<(std::ostream& rOStream,
                                 const DSS_FIC<TDim>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}

///@} // Fluid Dynamics Application group

} // namespace Kratos.

#endif // KRATOS_DSS_FIC_H
