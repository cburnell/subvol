#ifndef subvol_globalstatscollector_h__
#define subvol_globalstatscollector_h__


namespace subvol {
  enum class MessageType : int {
    EMPTY_MESSAGE,
    ROV_CHANGING_MESSAGE,
    SHOWN_BLOCKS_MESSAGE,
    MIN_RANGE_CHANGED_MESSAGE,
    MAX_RANGE_CHANGED_MESSAGE,
  };
  
  class Recipient;
  class Message {
  public:
    Message(MessageType t) 
      : type{ t }
    {
    }
    virtual ~Message() { }

    virtual void
      operator()(Recipient &r) { }

    MessageType type;
  };



} // namespace subvol



#endif  // !subvol_globalstatscollector_h__